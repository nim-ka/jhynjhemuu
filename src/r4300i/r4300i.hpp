#pragma once

#include "types.hpp"
#include "macros.hpp"

class R4300i;

#include "state.hpp"
#include "instruction.hpp"
#include "interp.hpp"

typedef void (*R4300iInstrFunction)(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram);

class R4300i {
	public:
		static R4300iInstrFunction instrJumpTable[];

		R4300i();

		R4300iState *get_state();
		void step(word *ram);
		void print();

		R4300iState *state;
};

