#pragma once

#include <thread>

#include "types.hpp"
#include "macros.hpp"

#include "r4300i.hpp"
#include "memory.hpp"

class System {
	public:
		System(std::string romName);

		void start();
		void stop();

		void step();

	private:
		R4300i *cpu;
		ROM *rom;
		RDRAM *ram;

		bool running;
		std::thread thread;
};
