#pragma once

#include "types.hpp"
#include "macros.hpp"

enum R4300iException {
	EXC_RESET,
	EXC_SOFT_RESET,
	EXC_ADDRESS_ERROR,
	EXC_TLB_REFILL,
	EXC_TLB_INVALID,
	EXC_TLB_MODIFIED,
	EXC_CACHE_ERROR,
	EXC_VIRTUAL_COHERENCY,
	EXC_BUS_ERROR,
	EXC_INTEGER_OVERFLOW,
	EXC_TRAP,
	EXC_SYSCALL,
	EXC_BREAKPOINT,
	EXC_RESERVED_INSTRUCTION,
	EXC_COPROCESSOR_UNUSABLE,
	EXC_FLOATING_POINT,
	EXC_WATCH,
	EXC_INTERRUPT
};

typedef void (*R4300iSecondPartFunction)(R4300i *cpu, byte *ram);

class R4300i {
	public:
		static R4300iInstrFunction instrJumpTable[];

		R4300i();

		void print();

		void step(byte *ram);
		void throw_exception(R4300iException exception);

		R4300iState *state;

		R4300iSecondPartFunction secondPart = NULL;
		dword isBranchLikely = false;
		dword secondPartTarget;
		dword secondPartCondition;

	private:
		void fetch_instruction(byte *ram);
		void execute_instruction(byte *ram);

		R4300iInstructionWrapper *curInstruction = NULL;
};
