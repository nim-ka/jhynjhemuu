#pragma once

#include "utils.hpp"
#include "r4300i.hpp"

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
		ROM(std::string filename);

		void attach_to_cpu(R4300i *cpu);

		byte read_byte(word offset);

		ROMHeader *header;

	private:
		R4300i *cpu;

		byte *data;
};
