#pragma once

#include "utils.hpp"
#include "r4300i.hpp"

class RDRAM {
	public:
		RDRAM(size_t size);

		void attach_to_cpu(R4300i *cpu);

		word virt_to_phys(word address);
		word phys_to_virt(word address);

		template <typename T> void read(word address, T *dest) {
			address = virt_to_phys(address);

			size_t size = sizeof(T);

			if (address % size) {
				//cpu->throw_exception(EXC_ADDRESS_ERROR);
			}

			*dest = 0;

			for (unsigned int i = 0; i < size; i++) {
				*dest <<= 8;
				*dest |= data[address + i];
			}
		}

		template <typename T> void write(word address, T src) {
			address = virt_to_phys(address);

			size_t size = sizeof(T);

			if (address % size) {
				//cpu->throw_exception(EXC_ADDRESS_ERROR);
			}

			for (unsigned int i = 0; i < size; i++) {
				data[address + i] = ((byte *) &src)[size - i - 1];
			}
		}

	private:
		byte *data;

		R4300i *cpu;
};
