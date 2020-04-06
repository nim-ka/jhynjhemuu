#include "utils.hpp"
#include "r4300i.hpp"

R4300iCOP0State::R4300iCOP0State(bool softResetOrNMI) {
	Random random = { 0 };
	random.data.random = 31;

	set_reg<Random>(cpRandom, random);

	PRId prId = { 0 };
	prId.data.imp = 0xE7; // ET
	prId.data.rev = 0xA5; // AS

	set_reg<PRId>(cpPrId, prId);

	Config config = { 0 };

	config.data.ec = 7; // 1:1.5; TODO: Is this right?
	config.data.ep = 0;
	config.data.pad2 = 0x6;
	config.data.be = 1;
	config.data.pad3 = 0x646;

	set_reg<Config>(cpConfig, config);

	Status status = { 0 };

	status.data.ts = 0;
	status.data.rp = 0;
	status.data.erl = 1;
	status.data.bev = 1;
	status.data.sr = softResetOrNMI;

	set_reg<Status>(cpStatus, status);
}

word R4300iCOP0State::get_reg_raw(R4300iCOP0Register reg) {
	return registers[reg];
}

void R4300iCOP0State::set_reg_raw(R4300iCOP0Register reg, word val) {
	if (reg == cpWired) {
		registers[cpRandom] = 31;
	}

	registers[reg] = val;
}

bool R4300iCOP0State::get_coc() {
	return coc;
}

void R4300iCOP0State::set_coc(bool val) {
	coc = val;
}

R4300iTLBEntry R4300iCOP0State::get_tlb_entry(int index) {
	return tlb[index];
}

void R4300iCOP0State::set_tlb_entry(int index, R4300iTLBEntry entry) {
	tlb[index] = entry;
}

void R4300iCOP0State::read_tlb_entry_regs(int index) {
	set_reg<PageMask>(cpPageMask, tlb[index].regs.pageMask);
	set_reg<EntryHi>(cpEntryHi, tlb[index].regs.entryHi);

	EntryLo entryLo0 = tlb[index].regs.entryLo0;
	EntryLo entryLo1 = tlb[index].regs.entryLo1;

	entryLo0.data.g = tlb[index].data.g;
	entryLo1.data.g = tlb[index].data.g;

	set_reg<EntryLo>(cpEntryLo0, entryLo0);
	set_reg<EntryLo>(cpEntryLo1, entryLo1);
}

void R4300iCOP0State::write_tlb_entry_regs(int index) {
	EntryLo entryLo0 = get_reg<EntryLo>(cpEntryLo0);
	EntryLo entryLo1 = get_reg<EntryLo>(cpEntryLo1);

	tlb[index].regs = {
		entryLo1,
		entryLo0,
		get_reg<EntryHi>(cpEntryHi),
		get_reg<PageMask>(cpPageMask)
	};

	tlb[index].data.g = entryLo0.data.g && entryLo1.data.g;
}

void R4300iCOP0State::print() {
	char buf[2048];

	sprintf(buf,
		"COP0 Regs\n"\
		"idx \t0x%08x\trnd \t0x%08x\tel0 \t0x%08x\tel1 \t0x%08x\n"\
		"ctx \t0x%08x\tpgm \t0x%08x\twrd \t0x%08x\tc7  \t0x%08x\n"\
		"bva \t0x%08x\tcnt \t0x%08x\tehi \t0x%08x\tcmp \t0x%08x\n"\
		"csr \t0x%08x\tcse \t0x%08x\tepc \t0x%08x\tpid \t0x%08x\n"\
		"cfg \t0x%08x\tlla \t0x%08x\twlo \t0x%08x\twhi \t0x%08x\n"\
		"xcx \t0x%08x\tc21 \t0x%08x\tc22 \t0x%08x\tc23 \t0x%08x\n"\
		"c24 \t0x%08x\tc25 \t0x%08x\tc26 \t0x%08x\tcer \t0x%08x\n"\
		"tlo \t0x%08x\tthi \t0x%08x\trpc \t0x%08x\tc31 \t0x%08x\n"\
		"coc \t%d\n\n",

		registers[0], registers[1], registers[2], registers[3],
		registers[4], registers[5], registers[6], registers[7],
		registers[8], registers[9], registers[10], registers[11],
		registers[12], registers[13], registers[14], registers[15],
		registers[16], registers[17], registers[18], registers[19],
		registers[20], registers[21], registers[22], registers[23],
		registers[24], registers[25], registers[26], registers[27],
		registers[28], registers[29], registers[30], registers[31],
		coc
	);

	info(buf);
}
