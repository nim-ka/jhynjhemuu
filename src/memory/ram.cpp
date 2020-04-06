#include "utils.hpp"
#include "r4300i.hpp"

#include "memory.hpp"

RDRAM::RDRAM(size_t size) {
	if (size != 0x400000 && size != 0x800000) {
		warn("Unexpected RAM size: " + std::to_string((double) size / 0x100000) + " MiB");
	}

	this->size = size;
	data = new byte[size];
}

void RDRAM::attach_to_cpu(R4300i *cpu) {
	debug_info("Attaching RAM to CPU");

	this->cpu = cpu;
	cpu->set_ram_ptr(this);
}

byte RDRAM::read_byte(word offset) {
	if (offset > size) {
		error("Could not read RAM at offset " + get_hex<word>(offset));
		return 0;
	}

	return data[offset];
}

void RDRAM::write_byte(word offset, byte val) {
	if (offset > size) {
		error("Could not write RAM at offset " + get_hex<word>(offset));
		return;
	}

	data[offset] = val;
}
