#include <string>

#include "utils.hpp"
#include "r4300i.hpp"

R4300i::R4300i() {
	state = new R4300iState();
}

void R4300i::print() {
	state->print();
}

void R4300i::fetch_instruction(byte *ram) {
	dword pc = state->get_pc();

	if ((pc & 0x3) != 0) {
		return throw_exception(EXC_ADDRESS_ERROR);
	}

	byte *opcodePtr = &ram[VIRT_TO_PHYS(pc)];
	word opcode = WORD_FROM_BYTE_PTR(opcodePtr);

	delete curInstruction;
	curInstruction = new R4300iInstructionWrapper(opcode);
}

void R4300i::execute_instruction(byte *ram) {
	if (curInstruction == NULL) {
		return error("Tried to execute instruction before fetching");
	}

	bool runSecondPart = false;
	bool runInstruction = true;

	if (secondPart != NULL) {
		runSecondPart = true;
	}

	if (isBranchLikely) {
		isBranchLikely = false;

		if (!secondPartCondition) {
			runInstruction = false;
		}
	}

	if (runInstruction) {
		instrJumpTable[curInstruction->instr](curInstruction, this, ram);
	}

	if (runSecondPart) {
		secondPart(this, ram);
		secondPart = NULL;
	}
}

void R4300i::step(byte *ram) {
	fetch_instruction(ram);
	execute_instruction(ram);
}

void R4300i::throw_exception (R4300iException exception) {
	warn("Received exception " + std::to_string(exception));
}
