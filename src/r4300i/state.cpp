#include "r4300i.hpp"

R4300iState::R4300iState() {}

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

float R4300iState::get_fpreg(R4300iFpRegister reg) {
	return fpregisters[reg];
}

void R4300iState::set_fpreg(R4300iFpRegister reg, float val) {
	fpregisters[reg] = val;
}

