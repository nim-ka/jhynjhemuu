#pragma once

#include "utils.hpp"
#include "r4300i.hpp"

class PIFROM {
	public:
		PIFROM(std::string filename);

		void attach_to_cpu(R4300i *cpu);

		byte read_byte(word offset);

	private:
		R4300i *cpu;

		byte *data;
};
