#pragma once

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

typedef enum {
	INSTR_NONE,
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
	INSTR_FABS,
	INSTR_FADD,
	INSTR_FBC1F,
	INSTR_FBC1FL,
	INSTR_FBC1T,
	INSTR_FBC1TL,
	INSTR_FCOMPARE,
	INSTR_FCEILL,
	INSTR_FCEILW,
	INSTR_FCFC1,
	INSTR_FCTC1,
	INSTR_FCVTD,
	INSTR_FCVTL,
	INSTR_FCVTS,
	INSTR_FCVTW,
	INSTR_FDIV,
	INSTR_FDMFC1,
	INSTR_FDMTC1,
	INSTR_FFLOORL,
	INSTR_FFLOORW,
	INSTR_FLDC1,
	INSTR_FLWC1,
	INSTR_FMFC1,
	INSTR_FMOV,
	INSTR_FMTC1,
	INSTR_FMUL,
	INSTR_FNEG,
	INSTR_FROUNDL,
	INSTR_FROUNDW,
	INSTR_FSDC1,
	INSTR_FSQRT,
	INSTR_FSUB,
	INSTR_FSWC1,
	INSTR_FTRUNCL,
	INSTR_FTRUNCW,
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
	INSTR_MFC0,
	INSTR_MFHI,
	INSTR_MFLO,
	INSTR_MTC0,
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
	INSTR_XORI
} R4300iInstruction;


// formats reversed because endianness issues
typedef union {
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
		word dest: 26;
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
} R4300iInstructionFormats;

class R4300iInstructionWrapper {
	public:
		R4300iInstructionWrapper(word value);

		R4300iInstruction instr;
		R4300iInstructionFormats *formats;
};

