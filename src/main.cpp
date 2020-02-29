#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <types.hpp>
#include <macros.hpp>

void open_romfile(std::filesystem::path filename, std::vector<byte> & dest)
{
	std::ifstream romfile (filename, std::ios::binary);
	dest.assign((std::istreambuf_iterator<char>(romfile)), std::istreambuf_iterator<char>());
};



int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}
	
	std::vector<byte> rom;
	open_romfile(argv[1], rom);
	
	unsigned long p = *(unsigned long *)rom.data();
	std::cout << std::hex << "0x" << __builtin_bswap32(p) << std::endl;
	
	return 0;
};