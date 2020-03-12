#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "r4300i.hpp"

class R4300iCOP0 {
	public:
		R4300iCOP0(R4300i *cpu);

		word virt_to_phys(word address);

	private:
		R4300i *cpu;
};
