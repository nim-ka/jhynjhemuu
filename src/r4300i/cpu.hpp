#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "memory.hpp"

enum R4300iException {
	EXC_RESET,
	EXC_NMI,
	EXC_ADDRESS_ERROR,
	EXC_TLB_MISS,
	EXC_TLB_INVALID,
	EXC_TLB_MOD,
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

typedef void (*R4300iSecondPartFunction)(R4300i *cpu, RDRAM *ram);

class R4300i {
	public:
		static R4300iInstrFunction instrJumpTable[];

		R4300i();

		void print();

		void set_pifrom_ptr(PIFROM *pifrom);
		void set_rom_ptr(ROM *rom);
		void set_ram_ptr(RDRAM *ram);

		void throw_exception(R4300iException exception);

		void start();
		void halt();

		void step();

		R4300iCOP0 *cop0;

		R4300iState *state;

		R4300iSecondPartFunction secondPart = NULL;
		dword isBranchLikely = false;
		dword secondPartTarget;
		dword secondPartCondition;

	private:
		void fetch_instruction();
		void execute_instruction();

		bool running = false;

		R4300iInstructionWrapper *curInstruction = NULL;

		PIFROM *pifrom;
		ROM *rom;
		RDRAM *ram;
};
