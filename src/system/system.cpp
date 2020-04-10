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
}

void System::start() {
	info("Starting system");

	started = true;
}

void System::stop() {
	info("Stopping system");

	stopped = true;
}

void System::step() {
	if (started) {
		cpu->start();
		running = true;
		started = false;
	}

	if (stopped) {
		cpu->stop();
		running = false;
		stopped = false;
	}

	if (!running) {
		return;
	}

	cpu->step();
//	rcp->step();
	cpu->step();
//	rcp->step();
	cpu->step();
}
