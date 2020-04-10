#include "utils.hpp"
#include "memory.hpp"

#include "r4300i.hpp"

#define STATE_GET_REG(fmt, name)     	cpu->state->get_reg(instr->formats-> fmt ## _format. name)
#define STATE_SET_REG(fmt, name, val)	cpu->state->set_reg(instr->formats-> fmt ## _format. name, val)

#define STATE_GET_COP0_REG(fmt, name)     	cpu->cop0->state->get_reg_raw((R4300iCOP0Register) instr->formats-> fmt ## _format. name)
#define STATE_SET_COP0_REG(fmt, name, val)	cpu->cop0->state->set_reg_raw((R4300iCOP0Register) instr->formats-> fmt ## _format. name, val)

#define ADVANCE_PC() cpu->state->set_pc(cpu->state->get_pc() + 4)

#define LINK(offset) cpu->state->set_reg(ra, cpu->state->get_pc() + (offset))

R4300iInstrFunction R4300i::instrJumpTable[] = {
	instr_none,
	instr_add,
	instr_addi,
	instr_addiu,
	instr_addu,
	instr_and,
	instr_andi,
	instr_beq,
	instr_beql,
	instr_bgez,
	instr_bgezal,
	instr_bgezall,
	instr_bgezl,
	instr_bgtz,
	instr_bgtzl,
	instr_blez,
	instr_blezl,
	instr_bltz,
	instr_bltzal,
	instr_bltzall,
	instr_bltzl,
	instr_bne,
	instr_bnel,
	instr_break,
	instr_dadd,
	instr_daddi,
	instr_daddiu,
	instr_daddu,
	instr_ddiv,
	instr_ddivu,
	instr_div,
	instr_divu,
	instr_dmult,
	instr_dmultu,
	instr_dsll,
	instr_dsll32,
	instr_dsllv,
	instr_dsra,
	instr_dsra32,
	instr_dsrav,
	instr_dsrl,
	instr_dsrl32,
	instr_dsrlv,
	instr_dsub,
	instr_dsubu,
	instr_eret,
	instr_j,
	instr_jal,
	instr_jalr,
	instr_jr,
	instr_lb,
	instr_lbu,
	instr_ld,
	instr_ldl,
	instr_ldr,
	instr_lh,
	instr_lhu,
	instr_ll,
	instr_lld,
	instr_lui,
	instr_lw,
	instr_lwl,
	instr_lwr,
	instr_lwu,
	instr_mfhi,
	instr_mflo,
	instr_mthi,
	instr_mtlo,
	instr_mult,
	instr_multu,
	instr_nor,
	instr_or,
	instr_ori,
	instr_sb,
	instr_sc,
	instr_scd,
	instr_sd,
	instr_sdl,
	instr_sdr,
	instr_sh,
	instr_sll,
	instr_sllv,
	instr_slt,
	instr_slti,
	instr_sltiu,
	instr_sltu,
	instr_sra,
	instr_srav,
	instr_srl,
	instr_srlv,
	instr_sub,
	instr_subu,
	instr_sw,
	instr_swl,
	instr_swr,
	instr_sync,
	instr_syscall,
	instr_teq,
	instr_teqi,
	instr_tge,
	instr_tgei,
	instr_tgeiu,
	instr_tgeu,
	instr_tlt,
	instr_tlti,
	instr_tltiu,
	instr_tltu,
	instr_tne,
	instr_tnei,
	instr_xor,
	instr_xori,
	instr_bc0f,
	instr_bc0fl,
	instr_bc0t,
	instr_bc0tl,
	instr_dmfc0,
	instr_dmtc0,
	instr_mfc0,
	instr_mtc0,
	instr_cache,
	instr_tlbp,
	instr_tlbr,
	instr_tlbwi,
	instr_tlbwr,
	instr_absf,
	instr_addf,
	instr_bc1f,
	instr_bc1fl,
	instr_bc1t,
	instr_bc1tl,
	instr_ceill,
	instr_ceilw,
	instr_cfc1,
	instr_ctc1,
	instr_cvtd,
	instr_cvtl,
	instr_cvts,
	instr_cvtw,
	instr_divf,
	instr_dmfc1,
	instr_dmtc1,
	instr_fcompare,
	instr_floorl,
	instr_floorw,
	instr_ldc1,
	instr_lwc1,
	instr_mfc1,
	instr_movf,
	instr_mtc1,
	instr_mulf,
	instr_negf,
	instr_roundl,
	instr_roundw,
	instr_sdc1,
	instr_sqrtf,
	instr_subf,
	instr_swc1,
	instr_truncl,
	instr_truncw
};

void instr_none(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->throw_exception({ EXC_RESERVED_INSTRUCTION });
}

void instr_add(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sword result = LOWER_WORD(source1 + source2);

	if (
		(source1 > 0 && source2 > 0 && result < 0) ||
		(source1 < 0 && source2 < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(result));
}

void instr_addi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source = STATE_GET_REG(i, source1);
	sword imm = SIGN_EXTEND_HWORD(instr->formats->i_format.imm);

	sword result = LOWER_WORD(source + imm);

	if (
		(source > 0 && imm > 0 && result < 0) ||
		(source < 0 && imm < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(i, source2, SIGN_EXTEND_WORD(result));
}

void instr_addiu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source = STATE_GET_REG(i, source1);
	sword imm = SIGN_EXTEND_HWORD(instr->formats->i_format.imm);

	sword result = LOWER_WORD(source + imm);

	STATE_SET_REG(i, source2, SIGN_EXTEND_WORD(result));
}

void instr_addu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sword result = LOWER_WORD(source1 + source2);

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(result));
}

void instr_and(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source1 & source2);
}

void instr_andi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(i, source1);
	sword imm = instr->formats->i_format.imm;

	STATE_SET_REG(i, source2, source & imm);
}

void instr_beq(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = STATE_GET_REG(i, source1) == STATE_GET_REG(i, source2);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_beql(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = STATE_GET_REG(i, source1) == STATE_GET_REG(i, source2);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bgez(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bgezal(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	LINK(8);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bgezall(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	LINK(8);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bgezl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bgtz(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) > 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bgtzl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) > 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_blez(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) <= 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_blezl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) <= 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bltz(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) < 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bltzal(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	LINK(8);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bltzall(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	LINK(8);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bltzl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = (sword) STATE_GET_REG(i, source1) >= 0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bne(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = STATE_GET_REG(i, source1) != STATE_GET_REG(i, source2);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bnel(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = STATE_GET_REG(i, source1) != STATE_GET_REG(i, source2);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_break(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->throw_exception({ EXC_BREAKPOINT });
}

void instr_dadd(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sdword result = source1 + source2;

	if (
		(source1 > 0 && source2 > 0 && result < 0) ||
		(source1 < 0 && source2 < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(r, dest, result);
}

void instr_daddi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source = STATE_GET_REG(i, source1);
	sword imm = SIGN_EXTEND_HWORD(instr->formats->i_format.imm);

	sdword result = source + imm;

	if (
		(source > 0 && imm > 0 && result < 0) ||
		(source < 0 && imm < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(i, source2, result);
}

void instr_daddiu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source = STATE_GET_REG(i, source1);
	sword imm = SIGN_EXTEND_HWORD(instr->formats->i_format.imm);

	sdword result = source + imm;

	STATE_SET_REG(i, source2, result);
}

void instr_daddu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sdword result = source1 + source2;

	if (
		(source1 > 0 && source2 > 0 && result < 0) ||
		(source1 < 0 && source2 < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(r, dest, result);
}

void instr_ddiv(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	cpu->state->set_lo(source1 / source2);
	cpu->state->set_hi(source1 % source2);
}

void instr_ddivu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	cpu->state->set_lo(source1 / source2);
	cpu->state->set_hi(source1 % source2);
}

void instr_div(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sword source1 = LOWER_WORD(STATE_GET_REG(r, source1));
	sword source2 = LOWER_WORD(STATE_GET_REG(r, source2));

	cpu->state->set_lo(SIGN_EXTEND_WORD(source1 / source2));
	cpu->state->set_hi(SIGN_EXTEND_WORD(source1 % source2));
}

void instr_divu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word source1 = LOWER_WORD(STATE_GET_REG(r, source1));
	word source2 = LOWER_WORD(STATE_GET_REG(r, source2));

	cpu->state->set_lo(SIGN_EXTEND_WORD(source1 / source2));
	cpu->state->set_hi(SIGN_EXTEND_WORD(source1 % source2));
}

void instr_dmult(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sqword result = source1 * source2;

	cpu->state->set_lo(LOWER_DWORD(result));
	cpu->state->set_hi(UPPER_DWORD(result));
}

void instr_dmultu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	qword source1 = STATE_GET_REG(r, source1);
	qword source2 = STATE_GET_REG(r, source2);

	qword result = source1 * source2;

	cpu->state->set_lo(LOWER_DWORD(result));
	cpu->state->set_hi(UPPER_DWORD(result));
}

void instr_dsll(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(r, source2);
	word shiftAmt = instr->formats->r_format.shiftAmt;

	STATE_SET_REG(r, dest, source << shiftAmt);
}

void instr_dsll32(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(r, source2);
	word shiftAmt = instr->formats->r_format.shiftAmt;

	STATE_SET_REG(r, dest, source << (32 + shiftAmt));
}

void instr_dsllv(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word shiftAmt = STATE_GET_REG(r, source1) & 0x3F; // lower 6 bits
	dword source = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source << shiftAmt);
}

void instr_dsra(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(r, source2);
	word shiftAmt = instr->formats->r_format.shiftAmt;

	int invShiftAmt = 64 - shiftAmt;

	STATE_SET_REG(r, dest, (source >> shiftAmt) | ((((dword) -1) >> invShiftAmt) << invShiftAmt));
}

void instr_dsra32(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(r, source2);
	word shiftAmt = instr->formats->r_format.shiftAmt + 32;

	int invShiftAmt = 64 - shiftAmt;

	STATE_SET_REG(r, dest, (source >> shiftAmt) | ((((dword) -1) >> invShiftAmt) << invShiftAmt));
}

void instr_dsrav(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word shiftAmt = STATE_GET_REG(r, source1) & 0x3F; // lower 6 bits
	dword source = STATE_GET_REG(r, source2);

	int invShiftAmt = 64 - shiftAmt;

	STATE_SET_REG(r, dest, (source >> shiftAmt) | ((((dword) -1) >> invShiftAmt) << invShiftAmt));
}

void instr_dsrl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(r, source2);
	word shiftAmt = instr->formats->r_format.shiftAmt;

	STATE_SET_REG(r, dest, source >> shiftAmt);
}

void instr_dsrl32(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(r, source2);
	word shiftAmt = instr->formats->r_format.shiftAmt;

	STATE_SET_REG(r, dest, source >> (32 + shiftAmt));
}

void instr_dsrlv(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word shiftAmt = STATE_GET_REG(r, source1) & 0x3F; // lower 6 bits
	dword source = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source >> shiftAmt);
}

void instr_dsub(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sdword result = source1 - source2;

	if (
		(source1 > 0 && source2 > 0 && result < 0) ||
		(source1 < 0 && source2 < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(r, dest, result);
}

void instr_dsubu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sdword result = source1 - source2;

	STATE_SET_REG(r, dest, result);
}

void instr_eret(R4300iInstructionWrapper *instr, R4300i *cpu) {
	Status status = cpu->cop0->state->get_reg<Status>(cpStatus);

	if (status.data.erl) {
		cpu->state->set_pc(cpu->cop0->state->get_reg<ErrorEPC>(cpErrorEPC).value);
		status.data.erl = 0;
	} else {
		cpu->state->set_pc(cpu->cop0->state->get_reg<EPC>(cpEPC).value);
		status.data.exl = 0;
	}

	cpu->state->set_llbit(false);
}

void instr_j(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = instr->formats->j_format.target;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		cpu->state->set_pc((cpu->state->get_pc() & 0xFFFFFFFFF0000000) | (cpu->secondPartTarget << 2));
	};
}

void instr_jal(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = instr->formats->j_format.target;

	LINK(8);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		cpu->state->set_pc((cpu->state->get_pc() & 0xFFFFFFFFF0000000) | (cpu->secondPartTarget << 2));
	};
}

void instr_jalr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = STATE_GET_REG(r, source1);

	LINK(8);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		cpu->state->set_pc(cpu->secondPartTarget);
	};
}

void instr_jr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = STATE_GET_REG(r, source1);

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		cpu->state->set_pc(cpu->secondPartTarget);
	};
}

void instr_lb(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, SIGN_EXTEND_BYTE_THRICE(cpu->cop0->read<byte>(base + offset)));
}

void instr_lbu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, cpu->cop0->read<byte>(base + offset));
}

void instr_ld(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, cpu->cop0->read<dword>(base + offset));
}

void instr_ldl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;
	word alignedAddress = address & ~7;
	int misalignment = address & 7;

	dword mem = cpu->cop0->read<dword>(alignedAddress);

	STATE_SET_REG(i, source2, (STATE_GET_REG(i, source2) & ((1 << (misalignment * 8)) - 1)) | (mem << (misalignment * 8)));
}

void instr_ldr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;
	word alignedAddress = address & ~7;
	int misalignment = address & 7;

	dword mem = cpu->cop0->read<dword>(alignedAddress);

	STATE_SET_REG(i, source2, (STATE_GET_REG(i, source2) & ~((1 << ((misalignment + 1) * 8)) - 1)) | (mem >> ((8 - misalignment - 1) * 8)));
}

void instr_lh(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, SIGN_EXTEND_HWORD_TWICE(cpu->cop0->read<hword>(base + offset)));
}

void instr_lhu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, cpu->cop0->read<hword>(base + offset));
}

void instr_ll(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	STATE_SET_REG(i, source2, SIGN_EXTEND_WORD(cpu->cop0->read<word>(address)));

	cpu->cop0->state->set_reg<LLAddr>(cpLLAddr, { cpu->cop0->virt_to_phys(address, false) });
	cpu->state->set_llbit(true);
}

void instr_lld(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	STATE_SET_REG(i, source2, cpu->cop0->read<dword>(address));

	cpu->cop0->state->set_reg<LLAddr>(cpLLAddr, { cpu->cop0->virt_to_phys(address, false) });
	cpu->state->set_llbit(true);
}

void instr_lui(R4300iInstructionWrapper *instr, R4300i *cpu) {
	STATE_SET_REG(i, source2, SIGN_EXTEND_WORD(instr->formats->i_format.imm << 16));
}

void instr_lw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, SIGN_EXTEND_WORD(cpu->cop0->read<word>(base + offset)));
}

void instr_lwl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;
	word alignedAddress = address & ~3;
	int misalignment = address & 3;

	word mem = cpu->cop0->read<word>(alignedAddress);

	STATE_SET_REG(i, source2, (STATE_GET_REG(i, source2) & ((1 << (misalignment * 8)) - 1)) | (mem << (misalignment * 8)));
}

void instr_lwr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;
	word alignedAddress = address & ~3;
	int misalignment = address & 3;

	word mem = cpu->cop0->read<word>(alignedAddress);

	STATE_SET_REG(i, source2, (STATE_GET_REG(i, source2) & ~((1 << ((misalignment + 1) * 8)) - 1)) | (mem >> ((4 - misalignment - 1) * 8)));
}

void instr_lwu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, cpu->cop0->read<word>(base + offset));
}

void instr_mfhi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	STATE_SET_REG(r, dest, cpu->state->get_hi());
}

void instr_mflo(R4300iInstructionWrapper *instr, R4300i *cpu) {
	STATE_SET_REG(r, dest, cpu->state->get_lo());
}

void instr_mthi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->state->set_hi(STATE_GET_REG(r, source1));
}

void instr_mtlo(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->state->set_lo(STATE_GET_REG(r, source1));
}

void instr_mult(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sword source1 = LOWER_WORD(STATE_GET_REG(r, source1));
	sword source2 = LOWER_WORD(STATE_GET_REG(r, source2));

	sdword result = source1 * source2;

	cpu->state->set_lo(LOWER_WORD(result));
	cpu->state->set_hi(UPPER_WORD(result));
}

void instr_multu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word source1 = LOWER_WORD(STATE_GET_REG(r, source1));
	word source2 = LOWER_WORD(STATE_GET_REG(r, source2));

	dword result = source1 * source2;

	cpu->state->set_lo(LOWER_WORD(result));
	cpu->state->set_hi(UPPER_WORD(result));
}

void instr_nor(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, ~(source1 | source2));
}

void instr_or(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source1 | source2);
}

void instr_ori(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(i, source1);
	word imm = instr->formats->i_format.imm;

	STATE_SET_REG(i, source2, source | imm);
}

void instr_sb(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	cpu->cop0->write<byte>(base + offset, STATE_GET_REG(i, source2) & 0xFF);
}

void instr_sc(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	bool llbit = cpu->state->get_llbit();

	if (llbit) {
		cpu->cop0->write<word>(address, STATE_GET_REG(i, source2));
	}

	STATE_SET_REG(i, source2, llbit);
}

void instr_scd(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	bool llbit = cpu->state->get_llbit();

	if (llbit) {
		cpu->cop0->write<dword>(address, STATE_GET_REG(i, source2));
	}

	STATE_SET_REG(i, source2, llbit);
}

void instr_sd(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	cpu->cop0->write<dword>(base + offset, STATE_GET_REG(i, source2));
}

// LDL/LDR/LWL/LWR solely use bitwise operations but we shouldn't do that for the stores
// because that would necessitate reading the memory before writing it, which would
// trigger a read address error first instead of a write address error if the address
// was invalid
void instr_sdl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	dword val = STATE_GET_REG(i, source2);

	word i = address;

	while (true) {
		cpu->cop0->write<byte>(i, (val >> ((7 - (i - address)) * 8)) & 0xFF);

		if (++i % 8) {
			break;
		}
	}
}

void instr_sdr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	dword val = STATE_GET_REG(i, source2);

	word i = address;

	while (true) {
		cpu->cop0->write<byte>(i, (val >> ((7 - (i - address)) * 8)) & 0xFF);

		if (i-- % 8) {
			break;
		}
	}
}

void instr_sh(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	cpu->cop0->write<hword>(base + offset, STATE_GET_REG(i, source2) & 0xFFFF);
}

void instr_sll(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word source = LOWER_WORD(STATE_GET_REG(r, source2));
	word shiftAmt = instr->formats->r_format.shiftAmt;

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(source << shiftAmt));
}

void instr_sllv(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word shiftAmt = STATE_GET_REG(r, source1) & 0x1F; // lower 5 bits
	word source = LOWER_WORD(STATE_GET_REG(r, source2));

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(source << shiftAmt));
}

void instr_slt(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source1 < source2);
}

void instr_slti(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(i, source1);
	sdword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, source1 < imm);
}

void instr_sltiu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(i, source1);
	dword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	STATE_SET_REG(i, source2, source1 < imm);
}

void instr_sltu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source1 < source2);
}

void instr_sra(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word source = LOWER_WORD(STATE_GET_REG(r, source2));
	word shiftAmt = instr->formats->r_format.shiftAmt;

	int invShiftAmt = 32 - shiftAmt;

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(((source >> shiftAmt) | ((((word) -1) >> invShiftAmt) << invShiftAmt))));
}

void instr_srav(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word shiftAmt = STATE_GET_REG(r, source1) & 0x1F; // lower 5 bits
	word source = LOWER_WORD(STATE_GET_REG(r, source2));

	int invShiftAmt = 32 - shiftAmt;

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(((source >> shiftAmt) | ((((word) -1) >> invShiftAmt) << invShiftAmt))));
}

void instr_srl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word source = LOWER_WORD(STATE_GET_REG(r, source2));
	word shiftAmt = instr->formats->r_format.shiftAmt;

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(source >> shiftAmt));
}

void instr_srlv(R4300iInstructionWrapper *instr, R4300i *cpu) {
	word shiftAmt = STATE_GET_REG(r, source1) & 0x1F; // lower 5 bits
	word source = LOWER_WORD(STATE_GET_REG(r, source2));

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(source >> shiftAmt));
}

void instr_sub(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sword result = LOWER_WORD(source1 - source2);

	if (
		(source1 > 0 && source2 > 0 && result < 0) ||
		(source1 < 0 && source2 < 0 && result > 0)
	) {
		return cpu->throw_exception({ EXC_ARITHMETIC_OVERFLOW });
	}

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(result));
}

void instr_subu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	sword result = LOWER_WORD(source1 - source2);

	STATE_SET_REG(r, dest, SIGN_EXTEND_WORD(result));
}

void instr_sw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	cpu->cop0->write<word>(base + offset, STATE_GET_REG(i, source2) & 0xFFFFFFFF);
}

void instr_swl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	word val = STATE_GET_REG(i, source2);

	word i = address;

	while (true) {
		cpu->cop0->write<byte>(i, (val >> ((3 - (i - address)) * 8)) & 0xFF);

		if (++i % 4) {
			break;
		}
	}
}

void instr_swr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword base = STATE_GET_REG(i, source1);
	dword offset = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	word address = base + offset;

	word val = STATE_GET_REG(i, source2);

	word i = address;

	while (true) {
		cpu->cop0->write<byte>(i, (val >> ((3 - (i - address)) * 8)) & 0xFF);

		if (i-- % 4) {
			break;
		}
	}
}

void instr_sync(R4300iInstructionWrapper *instr, R4300i *cpu) {
	// SYNC is a nop on R4300i
}

void instr_syscall(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->throw_exception({ EXC_SYSCALL });
}

void instr_teq(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	if (source1 == source2) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_teqi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(i, source1);
	sdword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	if (source1 == imm) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tge(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	if (source1 >= source2) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tgei(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(i, source1);
	sdword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	if (source1 >= imm) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tgeiu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(i, source1);
	dword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	if (source1 >= imm) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tgeu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	if (source1 >= source2) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tlt(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	if (source1 < source2) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tlti(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(i, source1);
	sdword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	if (source1 < imm) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tltiu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(i, source1);
	dword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	if (source1 < imm) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tltu(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	if (source1 < source2) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tne(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(r, source1);
	sdword source2 = STATE_GET_REG(r, source2);

	if (source1 != source2) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_tnei(R4300iInstructionWrapper *instr, R4300i *cpu) {
	sdword source1 = STATE_GET_REG(i, source1);
	sdword imm = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm);

	if (source1 != imm) {
		return cpu->throw_exception({ EXC_TRAP });
	}
}

void instr_xor(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source1 = STATE_GET_REG(r, source1);
	dword source2 = STATE_GET_REG(r, source2);

	STATE_SET_REG(r, dest, source1 ^ source2);
}

void instr_xori(R4300iInstructionWrapper *instr, R4300i *cpu) {
	dword source = STATE_GET_REG(i, source1);
	word imm = instr->formats->i_format.imm;

	STATE_SET_REG(i, source2, source ^ imm);
}

void instr_bc0f(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = !cpu->coc0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bc0fl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = !cpu->coc0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bc0t(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = cpu->coc0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_bc0tl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->isBranchLikely = true;

	cpu->secondPartTarget = SIGN_EXTEND_HWORD_TWICE(instr->formats->i_format.imm) << 2;
	cpu->secondPartCondition = cpu->coc0;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		if (cpu->secondPartCondition) {
			cpu->state->set_pc(cpu->state->get_pc() + cpu->secondPartTarget);
		} else {
			ADVANCE_PC();
		}
	};
}

void instr_dmfc0(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = STATE_GET_COP0_REG(r, dest);
	cpu->secondPartCondition = true;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		STATE_SET_REG(r, source2, cpu->secondPartTarget);
		ADVANCE_PC();
	};
}

void instr_dmtc0(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = STATE_GET_REG(r, source2);
	cpu->secondPartCondition = true;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		STATE_SET_COP0_REG(r, dest, cpu->secondPartTarget);
		ADVANCE_PC();
	};
}

void instr_mfc0(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = STATE_GET_COP0_REG(r, dest);
	cpu->secondPartCondition = true;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		STATE_SET_REG(r, source2, SIGN_EXTEND_WORD(cpu->secondPartTarget));
		ADVANCE_PC();
	};
}

void instr_mtc0(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->secondPartTarget = STATE_GET_REG(r, source2);
	cpu->secondPartCondition = true;

	cpu->secondPart = [](R4300iInstructionWrapper *instr, R4300i *cpu) {
		STATE_SET_COP0_REG(r, dest, SIGN_EXTEND_WORD(cpu->secondPartTarget));
		ADVANCE_PC();
	};
}

void instr_cache(R4300iInstructionWrapper *instr, R4300i *cpu) {
	warn("CACHE operation unimplemented; skipping");
}

void instr_tlbp(R4300iInstructionWrapper *instr, R4300i *cpu) {
	EntryHi entryHi = cpu->cop0->state->get_reg<EntryHi>(cpEntryHi);

	for (unsigned int i = 0; i < 32; i++) {
		R4300iTLBEntry entry = cpu->cop0->state->get_tlb_entry(i);

		if (
			(entry.data.vpn2 == entryHi.data.vpn2) &&
			(entry.data.g || (entry.data.asid == entryHi.data.asid))
		) {
			cpu->cop0->state->set_reg<Index>(cpIndex, { i });
		}
	}
}

void instr_tlbr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->cop0->state->read_tlb_entry_regs(cpu->cop0->state->get_reg<Index>(cpIndex).data.index);
}

void instr_tlbwi(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->cop0->state->write_tlb_entry_regs(cpu->cop0->state->get_reg<Index>(cpIndex).data.index);
}

void instr_tlbwr(R4300iInstructionWrapper *instr, R4300i *cpu) {
	cpu->cop0->state->write_tlb_entry_regs(cpu->cop0->state->get_reg<Random>(cpRandom).data.random);
}

void instr_absf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("ABS.fmt unimplemented");
}

void instr_addf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("ADD.fmt unimplemented");
}

void instr_bc1f(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("BC1F unimplemented");
}

void instr_bc1fl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("BC1FL unimplemented");
}

void instr_bc1t(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("BC1T unimplemented");
}

void instr_bc1tl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("BC1TL unimplemented");
}

void instr_ceill(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CEIL.L.fmt unimplemented");
}

void instr_ceilw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CEIL.W.fmt unimplemented");
}

void instr_cfc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CFC1 unimplemented");
}

void instr_ctc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CTC1 unimplemented");
}

void instr_cvtd(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CVT.D.fmt unimplemented");
}

void instr_cvtl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CVT.L.fmt unimplemented");
}

void instr_cvts(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CVT.S.fmt unimplemented");
}

void instr_cvtw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("CVT.W.fmt unimplemented");
}

void instr_divf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("DIV.fmt unimplemented");
}

void instr_dmfc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("DMFC1 unimplemented");
}

void instr_dmtc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("DMTC1 unimplemented");
}

void instr_fcompare(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("C.cond.fmt unimplemented");
}

void instr_floorl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("FLOOR.L.fmt unimplemented");
}

void instr_floorw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("FLOOR.W.fmt unimplemented");
}

void instr_ldc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("LDC1 unimplemented");
}

void instr_lwc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("LWC1 unimplemented");
}

void instr_mfc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("MFC1 unimplemented");
}

void instr_movf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("MOV.fmt unimplemented");
}

void instr_mtc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("MTC1 unimplemented");
}

void instr_mulf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("MUL.fmt unimplemented");
}

void instr_negf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("NEG.fmt unimplemented");
}

void instr_roundl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("ROUND.L.fmt unimplemented");
}

void instr_roundw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("ROUND.W.fmt unimplemented");
}

void instr_sdc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("SDC1 unimplemented");
}

void instr_sqrtf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("SQRT.fmt unimplemented");
}

void instr_subf(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("SUB.fmt unimplemented");
}

void instr_swc1(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("SWC1 unimplemented");
}

void instr_truncl(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("TRUNC.L.fmt unimplemented");
}

void instr_truncw(R4300iInstructionWrapper *instr, R4300i *cpu) {
	error("TRUNC.W.fmt unimplemented");
}
