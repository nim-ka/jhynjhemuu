#include <string>

#include "utils.hpp"
#include "r4300i.hpp"

R4300i::R4300i() {
	state = new R4300iState();

	state->set_reg(v1, 2);
	state->set_reg(a0, 3);
}

void R4300i::print() {
	state->print();
}

void R4300i::step(word *ram) {
	R4300iInstructionWrapper instr(ram[VIRT_TO_PHYS(state->get_pc())]);

	instrJumpTable[instr.instr](&instr, this, ram);
}

void R4300i::throw_exception (R4300iException exception) {
	warn("Received exception " + std::to_string(exception));
}
