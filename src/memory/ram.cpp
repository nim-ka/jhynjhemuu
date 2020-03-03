#include "utils.hpp"
#include "memory.hpp"

RDRAM::RDRAM(size_t size) {
	if (size != 0x400000 && size != 0x800000) {
		error("Unexpected RAM size: " + std::to_string((double) size / 0x100000) + " MiB");
	}

	data = new byte[size];
}

template <typename T> void RDRAM::read(word address, T *dest) {
	if (address % sizeof(T)) {
		error("Misaligned RAM read");
	}

	*dest = * (T *) &data[address];
}

template <typename T> void RDRAM::write(word address, T src) {
	if (address % sizeof(T)) {
		error("Misaligned RAM write");
	}

	* (T *) &data[address] = src;
}
