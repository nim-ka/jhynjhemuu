#include <string>

#include "utils.hpp"
#include "r4300i.hpp"

R4300i::R4300i() {
	state = new R4300iState();
}

void R4300i::print() {
	state->print();
}

void R4300i::step(byte *ram) {
	byte *opcodePtr = &ram[VIRT_TO_PHYS(state->get_pc())];
	word opcode = WORD_FROM_BYTE_PTR(opcodePtr);

	R4300iInstructionWrapper instr(opcode);

	instrJumpTable[instr.instr](&instr, this, ram);

	if (delaySlot != NULL) {

	}
}

void R4300i::throw_exception (R4300iException exception) {
	warn("Received exception " + std::to_string(exception));
}
