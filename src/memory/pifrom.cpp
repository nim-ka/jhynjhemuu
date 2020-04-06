#include <fstream>
#include <sstream>

#include "utils.hpp"
#include "r4300i.hpp"

#include "memory.hpp"

PIFROM::PIFROM(std::string filename) {
	debug_info("Loading PIFROM from " + std::string(filename));

	std::ifstream file(filename, std::ios::binary);

	file.seekg(0, std::ios_base::end);
	size_t size = file.tellg();

	file.seekg(0, std::ios_base::beg);

	data = new byte[size];

	file.read((char *) data, size);
}

void PIFROM::attach_to_cpu(R4300i *cpu) {
	debug_info("Attaching PIFROM to CPU");

	this->cpu = cpu;
	cpu->set_pifrom_ptr(this);
}

byte PIFROM::read_byte(word offset) {
	return data[offset];
}
