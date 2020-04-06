#pragma once

#include "utils.hpp"
#include "r4300i.hpp"

class RDRAM {
	public:
		RDRAM(size_t size);

		void attach_to_cpu(R4300i *cpu);

		byte read_byte(word offset);
		void write_byte(word offset, byte val);

	private:
		size_t size;
		byte *data;

		R4300i *cpu;
};
