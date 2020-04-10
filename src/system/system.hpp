#pragma once

#include <thread>

#include "types.hpp"
#include "macros.hpp"

#include "r4300i.hpp"
#include "memory.hpp"

class System {
	public:
		System(std::string pifromName, std::string romName);

		void start();
		void stop();

		void step();

		R4300i *cpu;
	private:

		PIFROM *pifrom;
		ROM *rom;
		RDRAM *ram;

		bool started = false;
		bool stopped = false;
		bool running = false;
};
