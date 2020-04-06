#include <iostream>
#include <thread>

#include "utils.hpp"
#include "r4300i.hpp"
#include "memory.hpp"

#include "system.hpp"

System::System(std::string pifromName, std::string romName) {
	debug_info("Initializing system...");

	cpu = new R4300i();

	pifrom = new PIFROM(pifromName);
	pifrom->attach_to_cpu(cpu);

	if (pifrom == NULL) {
		error("Failed to load PIFROM from " + romName);
	}

	rom = new ROM(romName);
	rom->attach_to_cpu(cpu);

	if (rom == NULL) {
		error("Failed to load ROM from " + romName);
	}

	info("ROM Name: " + std::string(rom->header->name));

	ram = new RDRAM(0x400000);
	ram->attach_to_cpu(cpu);

	debug_info("Finished initialization");

	debug_warn(get_hex<byte>(pifrom->read_byte(0)));
	debug_warn(get_hex<byte>(rom->read_byte(0)));
	cpu->cop0->write<dword>(0x80000000, 0x0123456789ABCDEFll);
	debug_warn(get_hex<dword>(cpu->cop0->read<dword>(0x80000000)));
}

void System::start() {
	debug_info("Starting system");

	running = true;
}

void System::stop() {
	debug_info("Stopping system");

	running = false;
}

void System::step() {
	if (!running) {
		return;
	}

	cpu->step();
//	rcp->step();
	cpu->step();
//	rcp->step();
	cpu->step();
}
