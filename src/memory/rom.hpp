#pragma once

#include <vector>

#include <endian.hpp>

typedef struct {
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

class ROM {
	public:
		ROM(char filename[]);

		byte get_byte(unsigned int offset);

		hword get_hword(unsigned int offset);

		word get_word(unsigned int offset);

		dword get_dword(unsigned int offset);

		ROMHeader *header;

	private:
		std::vector<byte> vecdata;
		be_uint32_t *data;
};
