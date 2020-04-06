#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "r4300i.hpp"

#define NO_ADDRESS 0xFFFFFFFF

class R4300iCOP0 {
	public:
		R4300iCOP0(R4300i *cpu);

		word virt_to_phys(word address, bool isWrite);

		template <typename T> T read(word address) {
			size_t size = sizeof(T);

			if (address % size) {
				cpu->throw_exception({ EXC_ADDRESS_ERROR_R });
				return 0;
			}

			T ret = 0;

			for (unsigned int i = 0; i < size; i++) {
				ret <<= 8;
				ret |= read_byte(address + i);
			}

			return ret;
		}

		template <typename T> void write(word address, T val) {
			size_t size = sizeof(T);

			if (address % size) {
				cpu->throw_exception({ EXC_ADDRESS_ERROR_W });
				return;
			}

			for (unsigned int i = 0; i < size; i++) {
				write_byte(address + i, (val >> ((size - i - 1) * 8)) & 0xFF);
			}
		}

		R4300iCOP0State *state;

	private:
		byte read_byte(word address);
		void write_byte(word address, byte val);

		R4300i *cpu;
};
