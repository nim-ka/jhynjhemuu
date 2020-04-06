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

	static_assert(sizeof(byte) == 1, "Byte type must be one byte. See include/types.hpp");
	static_assert(sizeof(hword) == 2, "Halfword type must be two bytes. See include/types.hpp");
	static_assert(sizeof(word) == 4, "Word type must be four bytes. See include/types.hpp");
	static_assert(sizeof(dword) == 8, "Doubleword type must be eight bytes. See include/types.hpp");
	static_assert(sizeof(qword) == 16, "Quadrupleword type must be sixteen bytes. See include/types.hpp");

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
