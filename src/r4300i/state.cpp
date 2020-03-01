#include <cstdio>

#include "utils.hpp"
#include "r4300i.hpp"

R4300iState::R4300iState() {
	fpwords = (word *) fpregisters;
}

word R4300iState::get_pc() {
	return pc;
}

void R4300iState::set_pc(word val) {
	pc = val;
}

word R4300iState::get_hi() {
	return hi;
}

void R4300iState::set_hi(word val) {
	hi = val;
}

word R4300iState::get_lo() {
	return lo;
}

void R4300iState::set_lo(word val) {
	lo = val;
}

// redundancy
word R4300iState::get_reg(R4300iRegister reg) {
	if (reg == r0 || reg == gp) {
		return 0;
	}

	return registers[reg];
}

void R4300iState::set_reg(R4300iRegister reg, word val) {
	if (reg != r0 && reg != gp) {
		registers[reg] = val;
	}
}

float R4300iState::get_cpreg(R4300iCpRegister reg) {
	return cpregisters[reg];
}

void R4300iState::set_cpreg(R4300iCpRegister reg, float val) {
	cpregisters[reg] = val;
}

float R4300iState::get_fpreg(R4300iFpRegister reg) {
	return fpregisters[reg];
}

void R4300iState::set_fpreg(R4300iFpRegister reg, float val) {
	fpregisters[reg] = val;
}

void R4300iState::print() {
	char buf[2048];

	sprintf(buf,
		"State dump:\n"\
		"CPU Regs\n"\
		"r0\t%08x\tat\t%08x\tv0\t%08x\tv1\t%08x\n"\
		"a0\t%08x\ta1\t%08x\ta2\t%08x\ta3\t%08x\n"\
		"t0\t%08x\tt1\t%08x\tt2\t%08x\tt3\t%08x\n"\
		"t4\t%08x\tt5\t%08x\tt6\t%08x\tt7\t%08x\n"\
		"s0\t%08x\ts1\t%08x\ts2\t%08x\ts3\t%08x\n"\
		"s4\t%08x\ts5\t%08x\ts6\t%08x\ts7\t%08x\n"\
		"t8\t%08x\tt9\t%08x\tk0\t%08x\tk1\t%08x\n"\
		"gp\t%08x\tsp\t%08x\ts8\t%08x\tra\t%08x\n"\
		"pc\t%08x\thi\t%08x\tlo\t%08x\n"\
		"COP0 Regs\n"\
		"c0\t%08x\tc1\t%08x\tc2\t%08x\tc3\t%08x\n"\
		"c4\t%08x\tc5\t%08x\tc6\t%08x\tc7\t%08x\n"\
		"c8\t%08x\tc9\t%08x\tc10\t%08x\tc11\t%08x\n"\
		"c12\t%08x\tc13\t%08x\tc14\t%08x\tc15\t%08x\n"\
		"FPU Regs\n"\
		"f0\t%08x\tf1\t%08x\tf2\t%08x\tf3\t%08x\n"\
		"f4\t%08x\tf5\t%08x\tf6\t%08x\tf7\t%08x\n"\
		"f8\t%08x\tf9\t%08x\tf10\t%08x\tf11\t%08x\n"\
		"f12\t%08x\tf13\t%08x\tf14\t%08x\tf15\t%08x\n"\
		"f16\t%08x\tf17\t%08x\tf18\t%08x\tf19\t%08x\n"\
		"f20\t%08x\tf21\t%08x\tf22\t%08x\tf23\t%08x\n"\
		"f24\t%08x\tf25\t%08x\tf26\t%08x\tf27\t%08x\n"\
		"f28\t%08x\tf29\t%08x\tf30\t%08x\tf31\t%08x",

		registers[0], registers[1], registers[2], registers[3],
		registers[4], registers[5], registers[6], registers[7],
		registers[8], registers[9], registers[10], registers[11],
		registers[12], registers[13], registers[14], registers[15],
		registers[16], registers[17], registers[18], registers[19],
		registers[20], registers[21], registers[22], registers[23],
		registers[24], registers[25], registers[26], registers[27],
		registers[28], registers[29], registers[30], registers[31],
		registers[32], registers[33], registers[34],

		cpregisters[0], cpregisters[1], cpregisters[2], cpregisters[3],
		cpregisters[4], cpregisters[5], cpregisters[6], cpregisters[7],
		cpregisters[8], cpregisters[9], cpregisters[10], cpregisters[11],
		cpregisters[12], cpregisters[13], cpregisters[14], cpregisters[15],


		fpwords[0], fpwords[1], fpwords[2], fpwords[3],
		fpwords[4], fpwords[5], fpwords[6], fpwords[7],
		fpwords[8], fpwords[9], fpwords[10], fpwords[11],
		fpwords[12], fpwords[13], fpwords[14], fpwords[15],
		fpwords[16], fpwords[17], fpwords[18], fpwords[19],
		fpwords[20], fpwords[21], fpwords[22], fpwords[23],
		fpwords[24], fpwords[25], fpwords[26], fpwords[27],
		fpwords[28], fpwords[29], fpwords[30], fpwords[31]
	);

	info(buf);
}
