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
	gp, sp, s8, fp = s8, ra
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

		word get_pc();
		void set_pc(word val);

		word get_reg(R4300iRegister reg);
		void set_reg(R4300iRegister reg, word val);

		float get_fpreg(R4300iFpRegister reg);
		void set_fpreg(R4300iFpRegister reg, float val);

	private:
		word pc;

		word registers[32];
		float fpregisters[32];
};

typedef union {
	word value;
	word opcode: 6;
} R4300iInstruction;

class R4300i {
	public:
		R4300i();

		void step(word *ram);

	private:
		R4300iState *state;
};
