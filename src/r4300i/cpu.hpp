#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "memory.hpp"

class R4300i {
	public:
		static R4300iInstrFunction instrJumpTable[];

		R4300i();

		void print();

		void set_pifrom_ptr(PIFROM *pifrom);
		void set_rom_ptr(ROM *rom);
		void set_ram_ptr(RDRAM *ram);

		void start();
		void stop();
		void halt();

		void step();

		void throw_exception(R4300iException exception);

		R4300iState *state;

		R4300iCOP0 *cop0;

		bool coc0;
		bool coc1;

		PIFROM *pifrom;
		ROM *rom;
		RDRAM *ram;

		R4300iInstrFunction secondPart = NULL;
		dword isBranchLikely = false;
		dword secondPartTarget;
		dword secondPartCondition;

		bool didColdReset = false;
		bool didSoftReset = false;
		bool didNMI = false;

	private:
		void handle_exception();

		void fetch_instruction();
		void execute_instruction();

		bool running = false;
		bool halted = false;

		R4300iInstructionWrapper *prevInstruction = NULL;
		R4300iInstructionWrapper *curInstruction = NULL;

		R4300iException exception;
};
