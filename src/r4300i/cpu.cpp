#include <string>

#include "utils.hpp"
#include "memory.hpp"

#include "r4300i.hpp"

R4300i::R4300i() {
	debug_info("Initializing CPU");

	cop0 = new R4300iCOP0(this);
	state = new R4300iState();

	state->set_pc(0xBFC00000);
}

void R4300i::print() {
	state->print();
}

void R4300i::set_pifrom_ptr(PIFROM *pifrom) {
	this->pifrom = pifrom;
}

void R4300i::set_rom_ptr(ROM *rom) {
	this->rom = rom;
}

void R4300i::set_ram_ptr(RDRAM *ram) {
	this->ram = ram;
}

void R4300i::start() {
	running = true;
}

void R4300i::stop() {
	running = false;
}

void R4300i::halt() {
	running = false;
	halted = true;
}

void R4300i::step() {
#ifdef DEBUG
	info("Began step");
#endif

	didColdReset = false;
	didSoftReset = false;
	didNMI = false;

	// TODO: How often does this actually update?
	Count count = cop0->state->get_reg<Count>(cpCount);
	count.data.count++;
	cop0->state->set_reg<Count>(cpCount, count);

	if (running && !halted) {
		fetch_instruction();
		execute_instruction();

		handle_exception();

		Random random = cop0->state->get_reg<Random>(cpRandom);
		Wired wired = cop0->state->get_reg<Wired>(cpWired);

		random.data.random--;

		if (random.data.random < wired.data.wired) {
			random.data.random = 31;
		}

		cop0->state->set_reg<Random>(cpRandom, random);
	}

	count = cop0->state->get_reg<Count>(cpCount);
	Compare compare = cop0->state->get_reg<Compare>(cpCompare);

	if (count.data.count == compare.data.compare) {
		Cause cause = cop0->state->get_reg<Cause>(cpCause);
		cause.data.ip |= 0x80;
		cop0->state->set_reg<Cause>(cpCause, cause);
	}

#ifdef DEBUG
	info("Completed step");
#endif
}

const int exceptionPriorities[] = {
	1,	// EXC_INTERRUPT
	4,	// EXC_TLB_MODIFICATION
	5,	// EXC_TLB_MISS_R
	15,	// EXC_TLB_MISS_W
	6,	// EXC_ADDRESS_ERROR_R
	16,	// EXC_ADDRESS_ERROR_W
	14,	// EXC_BUS_ERROR_F
	2,	// EXC_BUS_ERROR_LS
	13,	// EXC_SYSCALL
	12,	// EXC_BREAKPOINT
	10,	// EXC_RESERVED_INSTRUCTION
	11,	// EXC_COPROCESSOR_UNUSABLE
	8,	// EXC_ARITHMETIC_OVERFLOW
	9,	// EXC_TRAP
	0,	// EXC_14
	7,	// EXC_FLOATING_POINT
	0,	// EXC_16
	0,	// EXC_17
	0,	// EXC_18
	0,	// EXC_19
	0,	// EXC_20
	0,	// EXC_21
	0,	// EXC_22
	3,	// EXC_WATCH
	0,	// EXC_24
	0,	// EXC_25
	0,	// EXC_26
	0,	// EXC_27
	0,	// EXC_28
	0,	// EXC_29
	0,	// EXC_30
	0,	// EXC_31
	19,	// EXC_COLD_RESET
	18,	// EXC_SOFT_RESET
	17	// EXC_NMI
};

void R4300i::throw_exception(R4300iException newException) {
	if (exceptionPriorities[newException.exception] > exceptionPriorities[exception.exception]) {
		exception = newException;
	}
}

// TODO pg183
void R4300i::handle_exception() {
	if (exception.exception == EXC_NONE) {
		return;
	}

	warn("Received exception " + exceptionNames[exception.exception]);

	if (exception.exception < EXC_COLD_RESET) {
		Cause cause = cop0->state->get_reg<Cause>(cpCause);
		cause.data.exc = exception.exception;
		cop0->state->set_reg<Cause>(cpCause, cause);
	}

	Status status = cop0->state->get_reg<Status>(cpStatus);
	status.data.exl = 1;

	cop0->state->set_reg<Status>(cpStatus, status);

	switch (exception.exception) {
		case EXC_COLD_RESET:
			debug_info("Re-initializing system for cold reset");

			didColdReset = true;

			delete cop0;
			delete state;

			cop0 = new R4300iCOP0(this);
			state = new R4300iState();

			state->set_pc(0xBFC00000);
			break;

		case EXC_SOFT_RESET:
		case EXC_NMI:
			debug_info("Re-initializing system for soft reset/NMI");

			if (exception.exception == EXC_SOFT_RESET) {
				didSoftReset = true;
			} else {
				didNMI = true;
			}

			cop0->state->set_reg<ErrorEPC>(cpErrorEPC, { (word) state->get_pc() });

			state->set_pc(0xBFC00000);
			break;

		default:
			word epc = state->get_pc();

			if (secondPart != NULL) {
				epc -= 4;

				Cause cause = cop0->state->get_reg<Cause>(cpCause);
				cause.data.bd = 1;
				cop0->state->set_reg<Cause>(cpCause, cause);
			}

			cop0->state->set_reg<EPC>(cpEPC, { epc });

			if (exception.exception == EXC_TLB_MISS_R || exception.exception == EXC_TLB_MISS_W) {
				state->set_pc(status.data.bev ? 0xBFC00200 : 0x80000000);
			} else {
				state->set_pc(status.data.bev ? 0xBFC00380 : 0x80000180);
			}
	}
}

void R4300i::fetch_instruction() {
#ifdef DEBUG
	info("Fetching instruction");
#endif

	dword pc = state->get_pc();

#ifdef DEBUG
	info("PC: " + get_hex<dword>(pc));
#endif

	word opcode = cop0->read<word>(pc);

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
	info("Executing instruction " + get_hex<word>(curInstruction->formats->value) + ": " + curInstruction->disassemble());
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
