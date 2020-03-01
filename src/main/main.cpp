#include <iostream>

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
	word ram[] = {
		0x03E00008,
		0x2C8D3B29  // s=4=a0, t=13=t5, imm=0x3B29
	};

	cpu.step(ram);

	return 0;
}
