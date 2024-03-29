#include "utils.hpp"
#include "r4300i.hpp"

R4300iInstruction opcodeTable[] = {
	INSTR_NONE,	INSTR_NONE,	INSTR_J,	INSTR_JAL,	INSTR_BEQ,	INSTR_BNE,	INSTR_BLEZ,	INSTR_BGTZ,
	INSTR_ADDI,	INSTR_ADDIU,	INSTR_SLTI,	INSTR_SLTIU,	INSTR_ANDI,	INSTR_ORI,	INSTR_XORI,	INSTR_LUI,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_BEQL,	INSTR_BNEL,	INSTR_BLEZL,	INSTR_BGTZL,
	INSTR_DADDI,	INSTR_DADDIU,	INSTR_LDL,	INSTR_LDR,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_LB,	INSTR_LH,	INSTR_LWL,	INSTR_LW,	INSTR_LBU,	INSTR_LHU,	INSTR_LWR,	INSTR_LWU,
	INSTR_SB,	INSTR_SH,	INSTR_SWL,	INSTR_SW,	INSTR_SDL,	INSTR_SDR,	INSTR_SWR,	INSTR_CACHE,
	INSTR_LL,	INSTR_LWC1,	INSTR_NONE,	INSTR_NONE,	INSTR_LLD,	INSTR_LDC1,	INSTR_NONE,	INSTR_LD,
	INSTR_SC,	INSTR_SWC1,	INSTR_NONE,	INSTR_NONE,	INSTR_SCD,	INSTR_SDC1,	INSTR_NONE,	INSTR_SD
};

R4300iInstruction opcodeTableSpecial[] = {
	INSTR_SLL,	INSTR_NONE,	INSTR_SRL,	INSTR_SRA,	INSTR_SLLV,	INSTR_NONE,	INSTR_SRLV,	INSTR_SRAV,
	INSTR_JR,	INSTR_JALR,	INSTR_NONE,	INSTR_NONE,	INSTR_SYSCALL,	INSTR_BREAK,	INSTR_NONE,	INSTR_SYNC,
	INSTR_MFHI,	INSTR_MTHI,	INSTR_MFLO,	INSTR_MTLO,	INSTR_DSLLV,	INSTR_NONE,	INSTR_DSRLV,	INSTR_DSRAV,
	INSTR_MULT,	INSTR_MULTU,	INSTR_DIV,	INSTR_DIVU,	INSTR_DMULT,	INSTR_DMULTU,	INSTR_DDIV,	INSTR_DDIVU,
	INSTR_ADD,	INSTR_ADDU,	INSTR_SUB,	INSTR_SUBU,	INSTR_AND,	INSTR_OR,	INSTR_XOR,	INSTR_NOR,
	INSTR_NONE,	INSTR_NONE,	INSTR_SLT,	INSTR_SLTU,	INSTR_DADD,	INSTR_DADDU,	INSTR_DSUB,	INSTR_DSUBU,
	INSTR_TGE,	INSTR_TGEU,	INSTR_TLT,	INSTR_TLTU,	INSTR_TEQ,	INSTR_NONE,	INSTR_TNE,	INSTR_NONE,
	INSTR_DSLL,	INSTR_NONE,	INSTR_DSRL,	INSTR_DSRA,	INSTR_DSLL32,	INSTR_NONE,	INSTR_DSRL32,	INSTR_DSRA32
};

R4300iInstruction opcodeTableRegimm[] = {
	INSTR_BLTZ,	INSTR_BGEZ,	INSTR_BLTZL,	INSTR_BGEZL,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_TGEI,	INSTR_TGEIU,	INSTR_TLTI,	INSTR_TLTIU,	INSTR_TEQI,	INSTR_NONE,	INSTR_TNEI,	INSTR_NONE,
	INSTR_BLTZAL,	INSTR_BGEZAL,	INSTR_BLTZALL,	INSTR_BGEZALL,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE
};

R4300iInstruction opcodeTableCop0[] = {
	INSTR_MFC0,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_MTC0,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE
};

R4300iInstruction opcodeTableFpu[] = {
	INSTR_MFC1,	INSTR_DMFC1,	INSTR_CFC1,	INSTR_NONE,	INSTR_MTC1,	INSTR_DMTC1,	INSTR_CTC1,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE
};

R4300iInstruction opcodeTableFpuBc[] = { INSTR_BC1F, INSTR_BC1T, INSTR_BC1FL, INSTR_BC1TL };

R4300iInstruction opcodeTableFpuSDWL[] = {
	INSTR_ADDF,	INSTR_SUBF,	INSTR_MULF,	INSTR_DIVF,	INSTR_SQRTF,	INSTR_ABSF,	INSTR_MOVF,	INSTR_NEGF,
	INSTR_ROUNDL,	INSTR_TRUNCL,	INSTR_CEILL,	INSTR_FLOORL,	INSTR_ROUNDW,	INSTR_TRUNCW,	INSTR_CEILW,	INSTR_FLOORW,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_CVTS,	INSTR_CVTD,	INSTR_NONE,	INSTR_NONE,	INSTR_CVTW,	INSTR_CVTL,	INSTR_NONE,	INSTR_NONE,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,
	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE,	INSTR_FCOMPARE
};

R4300iInstructionWrapper::R4300iInstructionWrapper(word value) {
	formats.value = value;

	word opcode = formats.r_format.opcode;

	switch (opcode) {
		case OPC_SPECIAL:
			instr = opcodeTableSpecial[formats.r_format.function];
			break;

		case OPC_REGIMM:
			instr = opcodeTableRegimm[formats.i_format.source2];
			break;

		case OPC_COP0:
			instr = opcodeTableCop0[formats.c0_format.format];
			break;

		case OPC_COP1: {
			word format = formats.fm_format.format;

			switch (format) {
				case FPU_CODE_BC:
					instr = opcodeTableFpuBc[formats.fb_format.ndtf];
					break;

				case FPU_CODE_S:
				case FPU_CODE_D:
				case FPU_CODE_W:
				case FPU_CODE_L:
					instr = opcodeTableFpuSDWL[formats.fr_format.function];

					if (
						(
							(instr != INSTR_CVTS && instr != INSTR_CVTD) &&
							(format == FPU_CODE_W || format == FPU_CODE_L)
						) ||
						(instr == INSTR_CVTS && format == FPU_CODE_S) ||
						(instr == INSTR_CVTD && format == FPU_CODE_D)
					) {
						instr = INSTR_NONE;
					}

					break;

				default:
					instr = opcodeTableFpu[format];
			}

			break;
		}

		default:
			instr = opcodeTable[opcode];
	}
}

const std::string instrNames[] = {
	"???",
	"add",
	"addi",
	"addiu",
	"addu",
	"and",
	"andi",
	"beq",
	"beql",
	"bgez",
	"bgezal",
	"bgezall",
	"bgezl",
	"bgtz",
	"bgtzl",
	"blez",
	"blezl",
	"bltz",
	"bltzal",
	"bltzall",
	"bltzl",
	"bne",
	"bnel",
	"break",
	"dadd",
	"daddi",
	"daddiu",
	"daddu",
	"ddiv",
	"ddivu",
	"div",
	"divu",
	"dmult",
	"dmultu",
	"dsll",
	"dsll32",
	"dsllv",
	"dsra",
	"dsra32",
	"dsrav",
	"dsrl",
	"dsrl32",
	"dsrlv",
	"dsub",
	"dsubu",
	"eret",
	"j",
	"jal",
	"jalr",
	"jr",
	"lb",
	"lbu",
	"ld",
	"ldl",
	"ldr",
	"lh",
	"lhu",
	"ll",
	"lld",
	"lui",
	"lw",
	"lwl",
	"lwr",
	"lwu",
	"mfhi",
	"mflo",
	"mthi",
	"mtlo",
	"mult",
	"multu",
	"nor",
	"or",
	"ori",
	"sb",
	"sc",
	"scd",
	"sd",
	"sdl",
	"sdr",
	"sh",
	"sll",
	"sllv",
	"slt",
	"slti",
	"sltiu",
	"sltu",
	"sra",
	"srav",
	"srl",
	"srlv",
	"sub",
	"subu",
	"sw",
	"swl",
	"swr",
	"sync",
	"syscall",
	"teq",
	"teqi",
	"tge",
	"tgei",
	"tgeiu",
	"tgeu",
	"tlt",
	"tlti",
	"tltiu",
	"tltu",
	"tne",
	"tnei",
	"xor",
	"xori",
	"bc0f",
	"bc0fl",
	"bc0t",
	"bc0tl",
	"dmfc0",
	"dmtc0",
	"mfc0",
	"mtc0",
	"cache",
	"tlbp",
	"tlbr",
	"tlbwi",
	"tlbwr",
	"abs.",
	"add.",
	"bc1f",
	"bc1fl",
	"bc1t",
	"bc1tl",
	"ceil.l.",
	"ceil.w.",
	"cfc1",
	"ctc1",
	"cvt.d.",
	"cvt.l.",
	"cvt.s.",
	"cvt.w.",
	"div.",
	"dmfc1",
	"dmtc1",
	"c.",
	"floor.l.",
	"floor.w.",
	"ldc1",
	"lwc1",
	"mfc1",
	"mov.",
	"mtc1",
	"mul.",
	"neg.",
	"round.l.",
	"round.w.",
	"sdc1",
	"sqrt.",
	"sub.",
	"swc1",
	"trunc.l.",
	"trunc.w."
};

const std::string compareInstrNames[] = {
	"f",
	"un",
	"eq",
	"ueq",
	"olt",
	"ult",
	"ole",
	"ule",
	"sf",
	"ngle",
	"seq",
	"ngl",
	"lt",
	"nge",
	"le",
	"ngt"
};

// TODO: Full disasm
std::string R4300iInstructionWrapper::disassemble() {
	std::string name = instrNames[instr];

	if (instr == INSTR_FCOMPARE) {
		name += "." + compareInstrNames[formats.fc_format.cond];
	}

	for (unsigned int i = 0; i < sizeof(opcodeTableFpuSDWL) / sizeof(R4300iInstruction); i++) {
		if (instr == opcodeTableFpuSDWL[i]) {
			int format = formats.fr_format.format;
			name +=
				format == FPU_CODE_S ? "s" :
				format == FPU_CODE_D ? "d" :
				format == FPU_CODE_W ? "w" :
				format == FPU_CODE_L ? "l" : "?";
		}
	}

	return name;
}
