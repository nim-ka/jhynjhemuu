#include <fstream>
#include <sstream>

#include "utils.hpp"
#include "r4300i.hpp"

#include "memory.hpp"

ROM::ROM(std::string filename) {
	debug_info("Loading ROM from " + std::string(filename));

	std::ifstream file(filename, std::ios::binary);

	file.seekg(0, std::ios_base::end);
	size_t size = file.tellg();

	file.seekg(0, std::ios_base::beg);

	data = new byte[size];
	header = (ROMHeader *) data;

	file.read((char *) data, size);
}

void ROM::attach_to_cpu(R4300i *cpu) {
	debug_info("Attaching ROM to CPU");

	this->cpu = cpu;
	cpu->set_rom_ptr(this);
}

byte ROM::read_byte(word offset) {
	return data[offset];
}
