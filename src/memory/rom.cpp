#include <fstream>
#include <sstream>
#include <vector>

#include "utils.hpp"
#include "rom.hpp"

ROM::ROM(char filename[]) {
	std::ifstream file(filename, std::ios::binary);

	vecdata.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	if (vecdata.size() < 0x4000) {
		error("ROM must be at least 0x4000 bytes");
	}

	data = (be_uint32_t *) vecdata.data();
	header = (ROMHeader *) data;
}

byte ROM::get_byte(unsigned int offset) {
	return ((byte *)data)[offset];
}

hword ROM::get_hword(unsigned int offset) {
	return ((be_uint16_t *)data)[offset >> 1];
}

word ROM::get_word(unsigned int offset) {
	return data[offset >> 2];
}

dword ROM::get_dword(unsigned int offset) {
	return ((be_uint64_t *)data)[offset >> 3];
}
