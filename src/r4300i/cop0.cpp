
#include "utils.hpp"
#include "r4300i.hpp"

R4300iCOP0State::R4300iCOP0State() {
	Config config;

	config.data.ep = 0;
	config.data.pad2 = 0x6;
	config.data.be = 1;
	config.data.pad3 = 0x646;

	set_reg<Config>(cpConfig, config);

	Status status;

	status.data.ts = 0;
	status.data.rp = 0;
	status.data.erl = 1;
	status.data.bev = 1;
	status.data.sr = 0; // TODO: Should be 1 on soft reset/NMI

	set_reg<Status>(cpStatus, status);
}

word R4300iCOP0State::get_reg_raw(R4300iCOP0Register reg) {
	return registers[reg];
}

void R4300iCOP0State::set_reg_raw(R4300iCOP0Register reg, word val) {
	registers[reg] = val;
}

void R4300iCOP0State::read_tlb_entry(int index) {
	set_reg<PageMask>(cpPageMask, tlb[index].regs.pageMask);
	set_reg<EntryHi>(cpEntryHi, tlb[index].regs.entryHi);
	set_reg<EntryLo>(cpEntryLo0, tlb[index].regs.entryLo0);
	set_reg<EntryLo>(cpEntryLo1, tlb[index].regs.entryLo1);
}

void R4300iCOP0State::write_tlb_entry(int index) {
	tlb[index].regs = {
		get_reg<EntryLo>(cpEntryLo1),
		get_reg<EntryLo>(cpEntryLo0),
		get_reg<EntryHi>(cpEntryHi),
		get_reg<PageMask>(cpPageMask)
	};
}

R4300iCOP0::R4300iCOP0(R4300i *cpu) {
#ifdef DEBUG
	info("Initializing COP0");
#endif

	this->cpu = cpu;
	this->state = new R4300iCOP0State();
}

word R4300iCOP0::virt_to_phys(word address) {
	if (address >= 0x80000000 && address < 0xc0000000) {
		return address & 0x1FFFFFFF;
	} else {
		// TODO: This is probably horribly broken, see VR4300 man. pgs. 122-157
#ifdef DEBUG
		info("TLB lookup for address" + get_hex<word>(address));
#endif

		for (int i = 0; i < 32; i++) {
			state->read_tlb_entry(i);

			PageMask mask = state->get_reg<PageMask>(cpPageMask);
			EntryHi hi = state->get_reg<EntryHi>(cpEntryHi);
			EntryLo lo0 = state->get_reg<EntryLo>(cpEntryLo0);
			EntryLo lo1 = state->get_reg<EntryLo>(cpEntryLo1);

			int size = PAGE_SIZE(mask.data.mask);

			word vpn = address & ((~mask.data.mask) << 13);
			EntryLo lo = (address & size) ? lo1 : lo0;

			if ((vpn >> 1) == hi.data.vpn2 && (lo.data.g || state->asid == hi.data.asid)) {
				if (!lo.data.v) {
					cpu->throw_exception(EXC_TLB_INVALID);
					return 0;
				}

				if (!lo.data.d) {
					// TODO: Throw TLB Mod exception if write
				}

				// TODO: Cache?
				return (lo.data.pfn * size) | (address ^ vpn);
			}
		}

		cpu->throw_exception(EXC_TLB_MISS);
		return 0;
	}
}

// TODO: cop0 print
