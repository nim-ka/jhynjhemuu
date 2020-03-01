#include <string>

#include "utils.hpp"
#include "r4300i.hpp"

R4300i::R4300i() {
	state = new R4300iState();
}

void R4300i::step(word *ram) {
	R4300iInstructionWrapper instr(ram[VIRT_TO_PHYS(state->get_reg(pc))]);

	
}

void R4300i::print() {
	state->print();
}
