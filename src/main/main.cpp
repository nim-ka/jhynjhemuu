#include <iostream>
#include <cassert>
#include <cstdio>

#include "utils.hpp"
#include "r4300i.hpp"
#include "memory.hpp"

#include "main.hpp"

R4300i cpu;

ROM *rom;
RDRAM *ram;

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

	rom = new ROM(argv[1]);

	info("ROM Name: " + std::string(rom->header->name));

#ifdef DEBUG
	info(get_hex<word>(rom->header->PC));
#endif

	ram = new RDRAM(0x400000);

	ram->attach_to_cpu(&cpu);

	cpu.state->set_pc(rom->header->PC); // This should be automatic

	// testing stuff

	cpu.state->set_pc(0x80000000);
	cpu.state->set_reg(t0, 0x00001000);
	cpu.state->set_reg(t1, 0x00007000);

	byte program[] = {
		0x01, 0x09, 0x50, 0x20, // 00: add $t2, $t0, $t1
		0x21, 0x08, 0x44, 0x44, // 04: addi $t0, $t0, 0x4444
		0x21, 0x29, 0xE4, 0x44,	// 08: addi $t1, $t1, -0x1BBC
		0x11, 0x09, 0x00, 0x03,	// 0C: beq $t0, $t1, L18 (0x03)
		0x21, 0xCE, 0x55, 0x55,	// 10: addi $t6, $t6, 0x5555
		0x21, 0xCE, 0xEE, 0xEF, // 14: addi $t6, $t6, -0x1111
		0x21, 0xCE, 0x11, 0x11	// 18: addi $t6, $t6, 0x1111
	};

	for (word i = 0; i < sizeof(program); i++) {
		ram->write<byte>(i + 0x80000000, program[i]);
	}

	cpu.print();

	while (ram->virt_to_phys(cpu.state->get_pc()) < sizeof(program)) {
		info("-----");
		cpu.step();
		cpu.print();
	}

	return 0;
}
