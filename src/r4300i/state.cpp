#include "r4300i.hpp"

R4300iState::R4300iState() {}

word get_pc() {
	return pc;
}

void set_pc(word val) {
	pc = val;
}

// redundancy
word get_reg(R4300iRegister reg) {
	if (reg == r0 || reg == gp) {
		return 0;
	}

	return registers[reg];
}

void set_reg(R4300iRegister reg, word val) {
	if (reg != r0 && reg != gp) {
		registers[reg] = val;
	}
}

float get_fpreg(R4300iFpRegister reg) {
	return fpregisters[reg];
}

void set_fpreg(R4300iFpRegister reg, float val) {
	fpregisters[reg] = val;
}

