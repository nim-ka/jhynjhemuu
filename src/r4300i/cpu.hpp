#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "memory.hpp"

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

		PIFROM *pifrom;
		ROM *rom;
		RDRAM *ram;

		R4300iSecondPartFunction secondPart = NULL;
		dword isBranchLikely = false;
		dword secondPartTarget;
		dword secondPartCondition;

	private:
		void fetch_instruction();
		void execute_instruction();

		bool running = false;

		R4300iInstructionWrapper *curInstruction = NULL;
};
