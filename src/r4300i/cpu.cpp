#include <string>

#include "utils.hpp"
#include "memory.hpp"

#include "r4300i.hpp"

R4300i::R4300i() {
#ifdef DEBUG
	info("Initializing CPU");
#endif

	cop0 = new R4300iCOP0(this);
	state = new R4300iState();
}

void R4300i::print() {
	state->print();
}

void R4300i::set_ram_ptr(RDRAM *ram) {
	this->ram = ram;
}

void R4300i::fetch_instruction() {
#ifdef DEBUG
	info("Fetching instruction");
#endif

	dword pc = state->get_pc();

#ifdef DEBUG
	info("PC: " + get_hex<dword>(pc));
#endif

	if ((pc & 0x3) != 0) {
		return throw_exception(EXC_ADDRESS_ERROR);
	}

	word opcode;
	ram->read<word>(pc, &opcode);

	delete curInstruction;
	curInstruction = new R4300iInstructionWrapper(opcode);

#ifdef DEBUG
	info("Fetched instruction " + get_hex<word>(opcode));
#endif
}

void R4300i::execute_instruction() {
	if (curInstruction == NULL) {
		return error("Tried to execute instruction before fetching");
	}

#ifdef DEBUG
	info("Executing instruction " + get_hex<word>(curInstruction->formats->value) + ": " + get_hex<word>(curInstruction->instr));
#endif

	bool runSecondPart = false;
	bool runInstruction = true;

	if (secondPart != NULL) {
		runSecondPart = true;
#ifdef DEBUG
		info("Detected delay slot");
#endif
	}

	if (isBranchLikely) {
		isBranchLikely = false;

		if (!secondPartCondition) {
			runInstruction = false;
#ifdef DEBUG
			info("Instruction invalidated!");
#endif
		}
	}

	if (runInstruction) {
		instrJumpTable[curInstruction->instr](curInstruction, this, ram);
	}

#ifdef DEBUG
	info("Executed instruction");
#endif

	if (runSecondPart) {
#ifdef DEBUG
		info("Finishing previous instruction");
#endif
		secondPart(this, ram);
		secondPart = NULL;
#ifdef DEBUG
		info("Finished previous instruction");
#endif
	}

}

void R4300i::step() {
#ifdef DEBUG
	info("Began step");
#endif

	fetch_instruction();
	execute_instruction();

#ifdef DEBUG
	info("Completed step");
#endif
}

void R4300i::throw_exception(R4300iException exception) {
	warn("Received exception " + std::to_string(exception));
}
