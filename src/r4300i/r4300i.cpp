#include "r4300i.hpp"

R4300i::R4300i() {
	state = new R4300iState();

	state->set_reg(v1, 2);
	state->set_reg(a0, 3);
}

void R4300i::step(word *ram) {
	R4300iInstructionWrapper instr(ram[VIRT_TO_PHYS(state->get_pc())]);

	instrJumpTable[instr.instr](&instr, state, ram);
}

void R4300i::print() {
	state->print();
}
