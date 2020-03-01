#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>

#include <types.hpp>
#include <macros.hpp>

bool open_romfile(char filename[], std::vector<byte> & dest)
{
	std::ifstream romfile (filename, std::ios::binary);
	dest.assign((std::istreambuf_iterator<char>(romfile)), std::istreambuf_iterator<char>());

	if (dest.size() < 0x4000)
	{
		std::cerr << "Error: ROM must be at least 0x4000 bytes" << std::endl;
		return 1;
	}

	return 0;
}

class be_uint16_t
{
	public:
		be_uint16_t() : be_val_(0) { }

		be_uint16_t(const uint16_t &val) : be_val_(__builtin_bswap16(val)) { }

		operator uint16_t() const
		{
			return __builtin_bswap16(be_val_);
		}
	private:
		uint16_t be_val_;
} __attribute__((packed));

class be_uint32_t
{
	public:
		be_uint32_t() : be_val_(0) { }

		be_uint32_t(const uint32_t &val) : be_val_(__builtin_bswap32(val)) { }

		operator uint32_t() const
		{
			return __builtin_bswap32(be_val_);
		}
	private:
		uint32_t be_val_;
} __attribute__((packed));

typedef struct
{
	be_uint32_t PI_BSD_DOM1;
	be_uint32_t clock_rate;
	be_uint32_t PC;
	be_uint32_t release_address;
	be_uint32_t CRC1;
	be_uint32_t CRC2;
	byte unused[8];
	char name[20];
	byte unused2[4];
	be_uint32_t media_format;
	be_uint16_t cartridge_id;
	byte country_code;
	byte version;
	byte bootcode[4032];
} __attribute__((packed)) ROMHeader;

word *rom;

ROMHeader header;

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}

	std::vector<byte> rom_byte;

	if (open_romfile(argv[1], rom_byte))
	{
		return 1;
	}

	rom = new word[rom_byte.size()];

	memcpy(rom, rom_byte.data(), rom_byte.size());

	memcpy(&header, (byte *)rom, sizeof(ROMHeader));

	std::cout << std::hex << header.name << std::endl;

	unsigned long p = rom[0];
	std::cout << std::hex << "0x" << __builtin_bswap32(p) << std::endl;

	return 0;
}
