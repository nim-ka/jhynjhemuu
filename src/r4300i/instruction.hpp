#pragma once

#include "memory.hpp"

#define OPC_SPECIAL 000
#define OPC_REGIMM 001
#define OPC_COP0 020
#define OPC_COP1 021
#define OPC_COP2 022

#define FPU_CODE_BC 8
#define FPU_CODE_S 16
#define FPU_CODE_D 17
#define FPU_CODE_W 20
#define FPU_CODE_L 21

enum R4300iInstruction {
	// Dummy
	INSTR_NONE,

	// CPU
	INSTR_ADD,
	INSTR_ADDI,
	INSTR_ADDIU,
	INSTR_ADDU,
	INSTR_AND,
	INSTR_ANDI,
	INSTR_BEQ,
	INSTR_BEQL,
	INSTR_BGEZ,
	INSTR_BGEZAL,
	INSTR_BGEZALL,
	INSTR_BGEZL,
	INSTR_BGTZ,
	INSTR_BGTZL,
	INSTR_BLEZ,
	INSTR_BLEZL,
	INSTR_BLTZ,
	INSTR_BLTZAL,
	INSTR_BLTZALL,
	INSTR_BLTZL,
	INSTR_BNE,
	INSTR_BNEL,
	INSTR_BREAK,
	INSTR_DADD,
	INSTR_DADDI,
	INSTR_DADDIU,
	INSTR_DADDU,
	INSTR_DDIV,
	INSTR_DDIVU,
	INSTR_DIV,
	INSTR_DIVU,
	INSTR_DMULT,
	INSTR_DMULTU,
	INSTR_DSLL,
	INSTR_DSLL32,
	INSTR_DSLLV,
	INSTR_DSRA,
	INSTR_DSRA32,
	INSTR_DSRAV,
	INSTR_DSRL,
	INSTR_DSRL32,
	INSTR_DSRLV,
	INSTR_DSUB,
	INSTR_DSUBU,
	INSTR_ERET,
	INSTR_J,
	INSTR_JAL,
	INSTR_JALR,
	INSTR_JR,
	INSTR_LB,
	INSTR_LBU,
	INSTR_LD,
	INSTR_LDL,
	INSTR_LDR,
	INSTR_LH,
	INSTR_LHU,
	INSTR_LL,
	INSTR_LLD,
	INSTR_LUI,
	INSTR_LW,
	INSTR_LWL,
	INSTR_LWR,
	INSTR_LWU,
	INSTR_MFHI,
	INSTR_MFLO,
	INSTR_MTHI,
	INSTR_MTLO,
	INSTR_MULT,
	INSTR_MULTU,
	INSTR_NOR,
	INSTR_OR,
	INSTR_ORI,
	INSTR_SB,
	INSTR_SC,
	INSTR_SCD,
	INSTR_SD,
	INSTR_SDL,
	INSTR_SDR,
	INSTR_SH,
	INSTR_SLL,
	INSTR_SLLV,
	INSTR_SLT,
	INSTR_SLTI,
	INSTR_SLTIU,
	INSTR_SLTU,
	INSTR_SRA,
	INSTR_SRAV,
	INSTR_SRL,
	INSTR_SRLV,
	INSTR_SUB,
	INSTR_SUBU,
	INSTR_SW,
	INSTR_SWL,
	INSTR_SWR,
	INSTR_SYNC,
	INSTR_SYSCALL,
	INSTR_TEQ,
	INSTR_TEQI,
	INSTR_TGE,
	INSTR_TGEI,
	INSTR_TGEIU,
	INSTR_TGEU,
	INSTR_TLT,
	INSTR_TLTI,
	INSTR_TLTIU,
	INSTR_TLTU,
	INSTR_TNE,
	INSTR_TNEI,
	INSTR_XOR,
	INSTR_XORI,

	// COP0-related
	INSTR_BC0F,
	INSTR_BC0FL,
	INSTR_BC0T,
	INSTR_BC0TL,
	INSTR_DMFC0,
	INSTR_DMTC0,
	INSTR_MFC0,
	INSTR_MTC0,

	// TLB-related
	INSTR_CACHE,
	INSTR_TLBP,
	INSTR_TLBR,
	INSTR_TLBWI,
	INSTR_TLBWR,

	// FPU-related
	INSTR_ABSF,
	INSTR_ADDF,
	INSTR_BC1F,
	INSTR_BC1FL,
	INSTR_BC1T,
	INSTR_BC1TL,
	INSTR_CEILL,
	INSTR_CEILW,
	INSTR_CFC1,
	INSTR_CTC1,
	INSTR_CVTD,
	INSTR_CVTL,
	INSTR_CVTS,
	INSTR_CVTW,
	INSTR_DIVF,
	INSTR_DMFC1,
	INSTR_DMTC1,
	INSTR_FCOMPARE,
	INSTR_FLOORL,
	INSTR_FLOORW,
	INSTR_LDC1,
	INSTR_LWC1,
	INSTR_MFC1,
	INSTR_MOVF,
	INSTR_MTC1,
	INSTR_MULF,
	INSTR_NEGF,
	INSTR_ROUNDL,
	INSTR_ROUNDW,
	INSTR_SDC1,
	INSTR_SQRTF,
	INSTR_SUBF,
	INSTR_SWC1,
	INSTR_TRUNCL,
	INSTR_TRUNCW
};

// formats reversed because endianness issues
union R4300iInstructionFormats {
	word value;
	struct {
		word function: 6;
		word shiftAmt: 5;
		R4300iRegister dest: 5;
		R4300iRegister source2: 5;
		R4300iRegister source1: 5;
		word opcode: 6;
	} r_format;
	struct {
		hword imm;
		R4300iRegister source2: 5;
		R4300iRegister source1: 5;
		word opcode: 6;
	} i_format;
	struct {
		word target: 26;
		word opcode: 6;
	} j_format;
	struct {
		word sel: 3;
		word pad: 8;
		R4300iRegister dest: 5;
		R4300iRegister source: 5;
		word format: 5;
		word opcode: 6;
	} c0_format; // mfc0, mtc0
	struct {
		hword offset;
		R4300iFpRegister source: 5;
		word base: 5;
		word opcode: 6;
	} fls_format; // lwc1, swc1, etc
	struct {
		word pad: 11;
		R4300iFpRegister fpr: 5;
		R4300iRegister gpr: 5;
		word format: 5;
		word opcode: 6; // COP1
	} fm_format; // mfc1, mtc1, etc
	struct {
		hword offset;
		word ndtf: 2;
		word cc: 3;
		word format: 5; // BC
		word opcode: 6; // COP1
	} fb_format;
	struct {
		word function: 6;
		R4300iFpRegister dest: 5;
		R4300iFpRegister source1: 5;
		R4300iFpRegister source2: 5;
		word format: 5; // S/D/W/L
		word opcode: 6; // COP1
	} fr_format; // arithmetic/convert
	struct {
		word cond: 4;
		word pad: 4; // 0b00011
		word cc: 3;
		R4300iFpRegister source1: 5;
		R4300iFpRegister source2: 5;
		word format: 5; // S/D/W/L
		word opcode: 6; // COP1
	} fc_format; // c.cond.fmt
};

class R4300iInstructionWrapper {
	public:
		R4300iInstructionWrapper(word value);

		R4300iInstruction instr;
		R4300iInstructionFormats *formats;
};

typedef void (*R4300iInstrFunction)(R4300iInstructionWrapper *instr, R4300i *cpu, RDRAM *ram);
