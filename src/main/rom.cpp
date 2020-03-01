#include <fstream>
#include <sstream>
#include <vector>

#include "utils.hpp"
#include "main.hpp"

ROM::ROM(char filename[]) {
	std::ifstream file(filename, std::ios::binary);

	vecdata.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	if (vecdata.size() < 0x4000) {
		error("ROM must be at least 0x4000 bytes");
	}

	data = (word *) vecdata.data();
	header = (ROMHeader *) data;
}
