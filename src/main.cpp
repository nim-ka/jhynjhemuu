#include <iostream>
#include <fstream>
#include <vector>
#include <winsock2.h>
#include <cstdint>
#include <cstring>

#include <types.hpp>
#include <macros.hpp>

void open_romfile(char filename[], std::vector<byte> & dest)
{
	std::ifstream romfile (filename, std::ios::binary);
	dest.assign((std::istreambuf_iterator<char>(romfile)), std::istreambuf_iterator<char>());
};

class be_uint16_t
{
public:
		be_uint16_t() : be_val_(0) { }
		
		be_uint16_t(const uint16_t &val) : be_val_(htons(val)) { }
		
		operator uint16_t() const
		{
			return ntohs(be_val_);
		}
private:
		uint16_t be_val_;
} __attribute__((packed));

class be_uint32_t
{
public:
		be_uint32_t() : be_val_(0) { }
		
		be_uint32_t(const uint32_t &val) : be_val_(htons(val)) { }
		
		operator uint32_t() const
		{
			return ntohs(be_val_);
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

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}
	
	std::vector<byte> rom;
	open_romfile(argv[1], rom);
	
	if (rom.size() < 0x4000)
	{
		std::cerr << "Error: ROM must be at least 0x4000 bytes" << std::endl;
		return 1;
	}
	
	ROMHeader header;
	
	memcpy(&header, rom.data(), sizeof(ROMHeader));
	
	std::cout << std::hex << header.name << std::endl;
	
	unsigned long p = *(unsigned long *)rom.data();
	std::cout << std::hex << "0x" << __builtin_bswap32(p) << std::endl;
	
	return 0;
};