#include <iostream>
#include <cassert>
#include <cstdio>

#include "utils.hpp"
#include "r4300i.hpp"

#include "main.hpp"

int main(int argc, char **argv) {
	assert(sizeof(byte) == 1);
	assert(sizeof(hword) == 2);
	assert(sizeof(word) == 4);
	assert(sizeof(dword) == 8);
	assert(sizeof(qword) == 16);

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}

	ROM rom(argv[1]);

	std::cout << std::hex << rom.header->name << std::endl;

	std::cout << "Entrypoint: 0x" << std::hex << rom.header->PC << std::endl;

	R4300i cpu;
	cpu.state->set_pc(rom.header->PC);

	// testing stuff

	cpu.state->set_pc(0x00000000);
	cpu.state->set_reg(t0, 0x00001000);
	cpu.state->set_reg(t1, 0x00007000);

	byte ram[] = {
		0x01, 0x09, 0x50, 0x20, // 00: add $t2, $t0, $t1
		0x21, 0x08, 0x44, 0x44, // 04: addi $t0, $t0, 0x4444
		0x21, 0x29, 0xE4, 0x44,	// 08: addi $t1, $t1, -0x1BBC
		0x11, 0x09, 0x00, 0x03,	// 0C: beq $t0, $t1, L18 (0x03)
		0x21, 0xCE, 0x55, 0x55,	// 10: addi $t6, $t6, 0x5555
		0x21, 0xCE, 0xEE, 0xEF, // 14: addi $t6, $t6, -0x1111
		0x21, 0xCE, 0x11, 0x11	// 18: addi $t6, $t6, 0x1111
	};

	cpu.print();

	while (cpu.state->get_pc() < sizeof(ram)) {
		info("-----");
		cpu.step(ram);
		cpu.print();
	}

	return 0;
}
