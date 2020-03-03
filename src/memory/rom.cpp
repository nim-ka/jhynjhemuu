#include <fstream>
#include <sstream>
#include <vector>

#include "utils.hpp"
#include "memory.hpp"

ROM::ROM(char filename[]) {
	std::ifstream file(filename, std::ios::binary);

	file.seekg(0, std::ios_base::end);
	size_t size = file.tellg();

	file.seekg(0, std::ios_base::beg);

	data = new byte[size];
	header = (ROMHeader *) data;

	file.read((char *) data, size);
}

template <typename T> void ROM::read(word address, T *dest) {
	if (address % sizeof(T)) {
		error("Misaligned ROM read");
	}

	*dest = * (T *) &data[address];
}
