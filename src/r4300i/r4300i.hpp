#pragma once

#include "types.hpp"

typedef enum {
	r0, zero = r0,
	at,
	v0, v1,
	a0, a1, a2, a3,
	t0, t1, t2, t3, t4, t5, t6, t7,
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9,
	k0, k1,
	gp, sp, s8, fp = s8, ra,
	pc, hi, lo
} R4300iRegister;

typedef enum {
	f0, f1, f2, f3, f4, f5, f6, f7,
	f8, f9, f10, f11, f12, f13, f14, f15,
	f16, f17, f18, f19, f20, f21, f22, f23,
	f24, f25, f26, f27, f28, f29, f30, f31
} R4300iFpRegister;

class R4300iState {
	public:
		R4300iState();

		word get_reg(R4300iRegister reg);
		void set_reg(R4300iRegister reg, word val);

		float get_fpreg(R4300iFpRegister reg);
		void set_fpreg(R4300iFpRegister reg, float val);

	private:
		word registers[35];
		float fpregisters[32];
};

typedef union {
	word value;
	struct {
		word opcode: 6;
		word source1: 5;
		word source2: 5;
		word dest: 5;
		word shamt: 5;
		word funct: 6;
	} r_format;
	struct {
		word opcode: 6;
		word source1: 5;
		word source2: 5;
		hword imm;
	} i_format;
	struct {
		word opcode: 6;
		word dest: 26;
	} j_format;
	struct {
		word opcode: 6;
		word base: 5;
		word source: 5;
		hword offset;
	} fls_format; // lwc1, swc1, etc
	struct {
		word opcode: 6; // COP1
		word format: 5; // BC
		word cc: 3;
		word nd: 1;
		word tf: 1;
		hword offset;
	} fb_format;
	struct {
		word opcode: 6; // COP1
		word format: 5; // S/D/W/L
		word source2: 5;
		word source1: 5;
		word dest: 5;
		word function: 6;
	} fr_format; // arithmetic/convert
	struct {
		word opcode: 6; // COP1
		word format: 5; // S/D/W/L
		word source2: 5;
		word source1: 5;
		word cc: 3;
		word pad: 5; // 0b00011
		word cond: 4;
	} fc_format; // c.cond.fmt
} R4300iInstruction;

class R4300i {
	public:
		R4300i();

		void step(word *ram);

	private:
		R4300iState *state;
};
