#pragma once

#include "types.hpp"
#include "macros.hpp"

#include "r4300i.hpp"

#define PAGE_SIZE(mask) (((mask) + 1) << 12)

enum R4300iCOP0Register {
	cpIndex,	cpRandom,	cpEntryLo0,	cpEntryLo1,
	cpContext,	cpPageMask,	cpWired,	cp7,
	cpBadVAddr,	cpCount,	cpEntryHi,	cpCompare,
	cpStatus,	cpCause,	cpEPC,    	cpPrId,
	cpConfig,	cpLLAddr,	cpWatchLo,	cpWatchHi,
	cpXContext,	cp21,    	cp22,     	cp23,
	cp24,     	cp25,    	cp26,    	cpCacheErr,
	cpTagLo,	cpTagHi,	cpErrorEPC,	cp31
};

union Index {
	word value;
	struct {
		word index: 6;
		word pad: 25;
		word probe: 1;
	} data;
};

union Random {
	word value;
	struct {
		word random: 6;
		word pad: 26;
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

union Context {
	word value;
	struct {
		word pad: 4;
		word badVpn2: 19;
		word pteBase: 9;
	} data;
};

union PageMask {
	word value;
	struct {
		word pad2: 13;
		word mask: 12;
		word pad1: 7;
	} data;
};

union Wired {
	word value;
	struct {
		word wired: 6;
		word pad: 26;
	} data;
};

union BadVAddr {
	word value;
	struct {
		word badVAddr;
	} data;
};

union Count {
	word value;
	struct {
		word count;
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

union Compare {
	word value;
	struct {
		word compare;
	} data;
};

union Status {
	word value;
	struct {
		word ie: 1;
		word exl: 1;
		word erl: 1;
		word ksu: 2;
		word ux: 1;
		word sx: 1;
		word kx: 1;
		word im: 8;
		word de: 1;
		word ce: 1;
		word ch: 1;
		word pad2: 1;
		word sr: 1;
		word ts: 1;
		word bev: 1;
		word pad1: 1;
		word its: 1;
		word re: 1;
		word fr: 1;
		word rp: 1;
		word cu: 4;
	} data;
};

union Cause {
	word value;
	struct {
		word pad4: 2;
		word exc: 5;
		word pad3: 1;
		word ip: 8;
		word pad2: 12;
		word ce: 2;
		word pad1: 1;
		word bd: 1;
	} data;
};

union EPC {
	word value;
	struct {
		word epc;
	} data;
};

union PRId {
	word value;
	struct {
		word rev: 8;
		word imp: 8;
		word pad: 16;
	} data;
};

union Config {
	word value;
	struct {
		word k0: 3;
		word cu: 1;
		word pad3: 11;
		word be: 1;
		word pad2: 8;
		word ep: 4;
		word ec: 3;
		word pad1: 1;
	} data;
};

union LLAddr {
	word value;
	struct {
		word llAddr;
	} data;
};

union WatchLo {
	word value;
	struct {
		word w: 1;
		word r: 1;
		word pad: 1;
		word pAddr0: 29;
	} data;
};

union WatchHi {
	word value;
	struct {
		word pAddr1: 4;
		word pad: 28;
	} data;
};

union XContext {
	dword value;
	struct {
		word pad: 4;
		word badVpn2: 27;
		word r: 2;
		word pteBase: 31;
	} data;
};

union TagLo {
	word value;
	struct {
		word pad2: 6;
		word pState: 2;
		word pTagLo: 20;
		word pad1: 4;
	} data;
};

union ErrorEPC {
	word value;
	struct {
		word errorEpc;
	} data;
};

union R4300iTLBEntry {
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
		R4300iCOP0State(bool softResetOrNMI);

		word get_reg_raw(R4300iCOP0Register reg);
		void set_reg_raw(R4300iCOP0Register reg, word val);

		template <typename T> T get_reg(R4300iCOP0Register reg) {
			return { get_reg_raw(reg) };
		};

		template <typename T> void set_reg(R4300iCOP0Register reg, T val) {
			set_reg_raw(reg, val.value);
		};

		bool get_coc();
		void set_coc(bool val);

		R4300iTLBEntry get_tlb_entry(int index);
		void set_tlb_entry(int index, R4300iTLBEntry entry);

		void read_tlb_entry_regs(int index);
		void write_tlb_entry_regs(int index);

		void print();

	private:
		word registers[32] = {0};
		bool coc = false;

		R4300iTLBEntry tlb[32] = {0};
};
