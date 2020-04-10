#include <iostream>
#include <chrono>
#include <thread>

#include "utils.hpp"
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

	std::thread systemThread([&] () {
		while (running) {
			sys->step();
		}
	});

	sys->start();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	sys->stop();

	sys->cpu->print();

	running = false;

	systemThread.join();
	messageThread.join();

	return 0;
}
