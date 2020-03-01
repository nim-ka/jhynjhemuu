#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "state.hpp"
#include "instruction.hpp"

class R4300i {
	public:
		R4300i();

		void step(word *ram);

		void print();

	private:
		R4300iState *state;
};
