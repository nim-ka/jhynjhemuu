#include "utils.hpp"
#include "r4300i.hpp"

R4300iCOP0::R4300iCOP0(R4300i *cpu) {
	debug_info("Initializing COP0");

	this->cpu = cpu;
	this->state = new R4300iCOP0State(cpu->didSoftReset || cpu->didNMI);
}

word R4300iCOP0::virt_to_phys(word address, bool isWrite) {
	if (address >= 0x80000000 && address < 0xC0000000) {
		return address & 0x1FFFFFFF;
	} else {
		debug_info("TLB lookup for address " + get_hex<word>(address));

		int hits = 0;
		word pAddr;

		for (int i = 0; i < 32; i++) {
			R4300iTLBEntry entry = state->get_tlb_entry(i);

			PageMask mask = entry.regs.pageMask;
			EntryHi hi = entry.regs.entryHi;
			EntryLo lo0 = entry.regs.entryLo0;
			EntryLo lo1 = entry.regs.entryLo1;

			int size = PAGE_SIZE(mask.data.mask);

			byte asid = address >> 24;
			address &= 0x00FFFFFF;

			word vpn = address & ((~mask.data.mask) << 13);
			EntryLo lo = (address & size) ? lo1 : lo0;

			if ((vpn >> 1) == hi.data.vpn2 && (lo.data.g || asid == hi.data.asid)) {
				if (++hits > 1) {
					Status status = state->get_reg<Status>(cpStatus);
					status.data.ts = 1;

					state->set_reg<Status>(cpStatus, status);

					cpu->halt();
					error("TLB Shutdown.");
					return NO_ADDRESS;
				}

				if (!lo.data.v) {
					state->set_reg<BadVAddr>(cpBadVAddr, { address });

					cpu->throw_exception({ isWrite ? EXC_TLB_MISS_W : EXC_TLB_MISS_R, true });
					return NO_ADDRESS;
				}

				if (!lo.data.d && isWrite) {
					state->set_reg<BadVAddr>(cpBadVAddr, { address });

					cpu->throw_exception({ EXC_TLB_MODIFICATION });
					return NO_ADDRESS;
				}

				pAddr = (lo.data.pfn * size) | (address ^ vpn);
			}
		}

		if (!hits) {
			state->set_reg<BadVAddr>(cpBadVAddr, { address });

			Context context = state->get_reg<Context>(cpContext);
			context.data.badVpn2 = address >> 13;
			state->set_reg<Context>(cpContext, context);

			cpu->throw_exception({ isWrite ? EXC_TLB_MISS_W : EXC_TLB_MISS_R });
			return NO_ADDRESS;
		}

		return pAddr;
	}
}

byte R4300iCOP0::read_byte(word address) {
	address = virt_to_phys(address, false);

	if (address == NO_ADDRESS) {
		return 0xEE; // TODO: in interpreter, check if cpu is in exception state to make sure the op doesnt go through
	}

	WatchLo watchLo = state->get_reg<WatchLo>(cpWatchLo);

	if (watchLo.data.r && (address & ~7) == watchLo.data.pAddr0) {
		cpu->throw_exception({ EXC_WATCH });
	}

	// TODO: memory mapping
	if (address >= 0x1FC00000) {
		return cpu->pifrom->read_byte(address - 0x1FC00000);
	}

	return cpu->ram->read_byte(address);
}

void R4300iCOP0::write_byte(word address, byte val) {
	address = virt_to_phys(address, true);

	if (address == NO_ADDRESS) {
		return;
	}

	WatchLo watchLo = state->get_reg<WatchLo>(cpWatchLo);

	if (watchLo.data.w && (address & ~7) == watchLo.data.pAddr0) {
		cpu->throw_exception({ EXC_WATCH });
	}

	cpu->ram->write_byte(address, val);
}
