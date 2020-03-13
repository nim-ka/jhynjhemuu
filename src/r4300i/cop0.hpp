#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "r4300i.hpp"

#define PAGE_SIZE(mask) (((mask) + 1) << 12)

enum R4300iCpRegister {
	cpIndex,	cpRandom,	cpEntryLo0,	cpEntryLo1,
	cpContext,	cpPageMask,	cpWired,	cp7,
	cpBadVAddr,	cpCount,	cpEntryHi,	cpCompare,
	cpStatus,	cpCause,	cpEPC,    	cpPrId,
	cpConfig,	cpLLAddr,	cpWatchLo,	cpWatchHi,
	cpXContext,	cp21,    	cp22,     	cp23,
	cp24,     	cp25,    	cp26,    	cpCacheErr,
	cpTagLo,	cpTagHi,	cpErrorEPC,	cp31
};

union PageMask {
	word value;
	struct {
		word pad2: 13;
		word mask: 12;
		word pad1: 7;
	} data;
};

union EntryHi {
	word value;
	struct {
		word asid: 8;
		word pad1: 5;
		word vpn2: 19;
	} data;
};

union EntryLo {
	word value;
	struct {
		word g: 1;
		word v: 1;
		word d: 1;
		word c: 3;
		word pfn: 20;
		word pad1: 6;
	} data;
};

union TLBEntry {
	qword value;
	struct {
		EntryLo entryLo1;
		EntryLo entryLo0;
		EntryHi entryHi;
		PageMask pageMask;
	} regs;
	struct {
		word pad7: 1;
		word v2: 1;
		word d2: 1;
		word c2: 3;
		word pfn2: 20;
		word pad6: 6;
		word pad5: 1;
		word v1: 1;
		word d1: 1;
		word c1: 3;
		word pfn1: 20;
		word pad4: 6;
		word asid: 8;
		word pad3: 4;
		word g: 1;
		word vpn2: 19;
		word pad2: 13;
		word mask: 12;
		word pad1: 7;
	} data;
};

class R4300iCOP0State {
	public:
		R4300iCOP0State();

		word get_reg(R4300iCpRegister reg);
		void set_reg(R4300iCpRegister reg, word val);

		void read_tlb_entry(int index);
		void write_tlb_entry(int index);

		void print();

		byte asid; // ???

	private:
		word registers[32] = {0};
		TLBEntry tlb[32] = {0};
};

class R4300iCOP0 {
	public:
		R4300iCOP0(R4300i *cpu);

		word virt_to_phys(word address);

		R4300iCOP0State *state;

	private:
		R4300i *cpu;
};
