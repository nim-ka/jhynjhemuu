#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "state.hpp"
#include "instruction.hpp"
#include "interp.hpp"

typedef void (*R4300iInstrFunction)(R4300iInstructionWrapper *instr, R4300iState *state, word *ram);

class R4300i {
	public:
		R4300i();

		void step(word *ram);

		void print();

		static R4300iInstrFunction instrJumpTable[];

	private:
		R4300iState *state;
};
