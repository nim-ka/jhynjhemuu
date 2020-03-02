#include <iostream>

#include "utils.hpp"
#include "r4300i.hpp"

#include "main.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}

	ROM rom(argv[1]);

	std::cout << std::hex << rom.header->name << std::endl;

	unsigned long p = rom.data[0];
	std::cout << std::hex << "0x" << __builtin_bswap32(p) << std::endl;

	// testing stuff
	R4300i cpu;

	byte ram[] = {
		0x00, 0x83, 0x28, 0x20, // add $a1, $a0, $v1
	};

	cpu.print();

	while (cpu.state->get_pc() < sizeof(ram)) {
		info("-----");
		cpu.step(ram);
		cpu.print();
	}

	return 0;
}
