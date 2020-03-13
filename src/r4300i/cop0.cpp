#include "utils.hpp"
#include "r4300i.hpp"

R4300iCOP0State::R4300iCOP0State() {}

word R4300iCOP0State::get_reg(R4300iCpRegister reg) {
	return registers[reg];
}

void R4300iCOP0State::set_reg(R4300iCpRegister reg, word val) {
	registers[reg] = val;
}

void R4300iCOP0State::read_tlb_entry(int index) {
	set_reg(cpPageMask, tlb[index].regs.pageMask.value);
	set_reg(cpEntryHi, tlb[index].regs.entryHi.value);
	set_reg(cpEntryLo0, tlb[index].regs.entryLo0.value);
	set_reg(cpEntryLo1, tlb[index].regs.entryLo1.value);
}

void R4300iCOP0State::write_tlb_entry(int index) {
	tlb[index].regs = {
		{ get_reg(cpPageMask) },
		{ get_reg(cpEntryHi) },
		{ get_reg(cpEntryLo0) },
		{ get_reg(cpEntryLo1) }
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

			PageMask mask = { state->get_reg(cpPageMask) };
			EntryHi hi = { state->get_reg(cpEntryHi) };
			EntryLo lo0 = { state->get_reg(cpEntryLo0) };
			EntryLo lo1 = { state->get_reg(cpEntryLo1) };

			EntryLo lo = (address & 0x1000) ? lo1 : lo0;

			word vpn = address & ((~mask.data.mask) << 13);

			if (vpn == hi.data.vpn2 && (lo.data.g || state->asid == hi.data.asid)) {
				if (!lo.data.v) {
					cpu->throw_exception(EXC_TLB_INVALID);
					return 0;
				}

				if (!lo.data.d) {
					// TODO: Throw TLB Mod exception if write
				}

				// TODO: Cache?
				return lo.data.pfn | (address ^ vpn);
			}
		}

		cpu->throw_exception(EXC_TLB_MISS);
		return 0;
	}
}

// TODO: cop0 print
