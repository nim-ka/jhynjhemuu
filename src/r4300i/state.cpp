#include <cstdio>

#include "utils.hpp"
#include "r4300i.hpp"

R4300iState::R4300iState() {
	fpdwords = (dword *) fpregisters;
}

dword R4300iState::get_pc() {
	return pc;
}

void R4300iState::set_pc(dword val) {
	pc = val;
}

dword R4300iState::get_hi() {
	return hi;
}

void R4300iState::set_hi(dword val) {
	hi = val;
}

dword R4300iState::get_lo() {
	return lo;
}

void R4300iState::set_lo(dword val) {
	lo = val;
}

bool R4300iState::get_llbit() {
	return llbit;
}

void R4300iState::set_llbit(bool val) {
	llbit = val;
}

// redundancy
dword R4300iState::get_reg(R4300iRegister reg) {
	if (reg == r0 || reg == gp) {
		return 0;
	}

	return registers[reg];
}

void R4300iState::set_reg(R4300iRegister reg, dword val) {
	if (reg != r0 && reg != gp) {
		registers[reg] = val;
	}
}

double R4300iState::get_fpreg(R4300iFpRegister reg) {
	return fpregisters[reg];
}

void R4300iState::set_fpreg(R4300iFpRegister reg, double val) {
	fpregisters[reg] = val;
}

void R4300iState::print() {
	char buf[2048];

	sprintf(buf,
		"CPU Regs\n"\
		"r0 \t0x%016lx\tat \t0x%016lx\tv0 \t0x%016lx\tv1 \t0x%016lx\n"\
		"a0 \t0x%016lx\ta1 \t0x%016lx\ta2 \t0x%016lx\ta3 \t0x%016lx\n"\
		"t0 \t0x%016lx\tt1 \t0x%016lx\tt2 \t0x%016lx\tt3 \t0x%016lx\n"\
		"t4 \t0x%016lx\tt5 \t0x%016lx\tt6 \t0x%016lx\tt7 \t0x%016lx\n"\
		"s0 \t0x%016lx\ts1 \t0x%016lx\ts2 \t0x%016lx\ts3 \t0x%016lx\n"\
		"s4 \t0x%016lx\ts5 \t0x%016lx\ts6 \t0x%016lx\ts7 \t0x%016lx\n"\
		"t8 \t0x%016lx\tt9 \t0x%016lx\tk0 \t0x%016lx\tk1 \t0x%016lx\n"\
		"gp \t0x%016lx\tsp \t0x%016lx\ts8 \t0x%016lx\tra \t0x%016lx\n"\
		"pc \t0x%016lx\thi \t0x%016lx\tlo \t0x%016lx\tll \t%d\n\n",

		registers[0], registers[1], registers[2], registers[3],
		registers[4], registers[5], registers[6], registers[7],
		registers[8], registers[9], registers[10], registers[11],
		registers[12], registers[13], registers[14], registers[15],
		registers[16], registers[17], registers[18], registers[19],
		registers[20], registers[21], registers[22], registers[23],
		registers[24], registers[25], registers[26], registers[27],
		registers[28], registers[29], registers[30], registers[31],
		pc, hi, lo, llbit
	);

	info(buf);
}
