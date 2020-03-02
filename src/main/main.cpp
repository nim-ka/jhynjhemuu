#include <iostream>
#include <cstdio>

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

	// testing stuff
	R4300i cpu;

	cpu.state->set_reg(t0, 0x00010000);
	cpu.state->set_reg(t1, 0x00030000);

	std::cout << "Entrypoint: 0x" << std::hex << rom.header->PC << std::endl;

	cpu.state->set_pc(rom.header->PC);

	byte ram[] = {
		0x01, 0x09, 0x50, 0x20, // add $t2, $t0, $t1
		0x21, 0x08, 0x44, 0x44, // addi $t0, $t0, 0x4444
	};

	cpu.print();

	while (cpu.state->get_pc() < sizeof(ram)) {
		info("-----");
		cpu.step(ram);
		cpu.print();
	}

	return 0;
}
