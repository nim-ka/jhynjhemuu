#include <iostream>
#include <cstdio>
#include <thread>

#include "utils.hpp"
#include "r4300i.hpp"
#include "memory.hpp"
#include "system.hpp"

#include "main.hpp"

System *sys;

int main(int argc, char **argv) {
	bool running = true;

	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << " <pifrom> <rom>" << std::endl;
		return 1;
	}

	std::thread messageThread([&] () {
		while (running || update_message_queue());
	});

	sys = new System(argv[1], argv[2]);

	running = false;
	messageThread.join();

	return 0;
}
