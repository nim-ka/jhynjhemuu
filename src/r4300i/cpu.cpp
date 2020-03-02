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

void R4300i::step(byte *ram) {
	byte *opcodePtr = &ram[VIRT_TO_PHYS(state->get_pc())];
	word opcode = (opcodePtr[0] << 24) | (opcodePtr[1] << 16) | (opcodePtr[2] << 8) | opcodePtr[3];

	R4300iInstructionWrapper instr(opcode);

	instrJumpTable[instr.instr](&instr, this, ram);
}

void R4300i::throw_exception (R4300iException exception) {
	warn("Received exception " + std::to_string(exception));
}
