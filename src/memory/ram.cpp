#include "utils.hpp"
#include "r4300i.hpp"

#include "memory.hpp"

RDRAM::RDRAM(size_t size) {
	if (size != 0x400000 && size != 0x800000) {
		error("Unexpected RAM size: " + std::to_string((double) size / 0x100000) + " MiB");
	}

	data = new byte[size];
}

void RDRAM::attach_to_cpu(R4300i *cpu) {
	debug_info("Attaching RAM to CPU");

	this->cpu = cpu;
	cpu->set_ram_ptr(this);
}

word RDRAM::virt_to_phys(word address) {
	return cpu->cop0->virt_to_phys(address);
}

