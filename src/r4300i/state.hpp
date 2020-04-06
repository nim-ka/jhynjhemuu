#pragma once

enum R4300iRegister {
	r0, zero = r0,
	at,
	v0, v1,
	a0, a1, a2, a3,
	t0, t1, t2, t3, t4, t5, t6, t7,
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9,
	k0, k1,
	gp, sp, s8, fp = s8, ra
};

enum R4300iFpRegister {
	f0, f1, f2, f3, f4, f5, f6, f7,
	f8, f9, f10, f11, f12, f13, f14, f15,
	f16, f17, f18, f19, f20, f21, f22, f23,
	f24, f25, f26, f27, f28, f29, f30, f31
};

class R4300iState {
	public:
		R4300iState();

		dword get_pc();
		void set_pc(dword val);

		dword get_hi();
		void set_hi(dword val);

		dword get_lo();
		void set_lo(dword val);

		bool get_llbit();
		void set_llbit(bool val);

		dword get_reg(R4300iRegister reg);
		void set_reg(R4300iRegister reg, dword val);

		// TODO: separate into cop1.cpp and merge this file with cpu?
		double get_fpreg(R4300iFpRegister reg);
		void set_fpreg(R4300iFpRegister reg, double val);

		void print();

	private:
		dword pc = 0;
		dword hi = 0;
		dword lo = 0;
		bool llbit = false;

		dword registers[35] = {0};
		double fpregisters[32] = {0};

		dword *fpdwords;
};
