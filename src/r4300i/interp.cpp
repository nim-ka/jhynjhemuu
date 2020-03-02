#include "utils.hpp"
#include "r4300i.hpp"

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

void instr_none(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	error("Tried to execute nil instruction");
}

// THIS IS NOT THE ACTUAL BEHAVIOR OF add, JUST A TEST
void instr_add(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	cpu->state->set_reg(instr->formats->r_format.dest,
		cpu->state->get_reg(instr->formats->r_format.source1) +
		cpu->state->get_reg(instr->formats->r_format.source2));
}

void instr_addi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_addiu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_addu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_and(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_andi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_beq(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_beql(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bgez(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bgezal(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bgezall(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bgezl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bgtz(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bgtzl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_blez(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_blezl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bltz(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bltzal(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bltzall(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bltzl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bne(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bnel(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_break(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dadd(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_daddi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_daddiu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_daddu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ddiv(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ddivu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_div(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_divu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dmult(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dmultu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsll(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsll32(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsllv(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsra(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsra32(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsrav(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsrl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsrl32(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsrlv(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsub(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dsubu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_eret(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_j(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_jal(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_jalr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_jr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lb(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lbu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ld(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ldl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ldr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lh(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lhu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ll(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lld(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lui(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lwl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lwr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lwu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mfhi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mflo(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mthi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mtlo(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mult(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_multu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_nor(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_or(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ori(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sb(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sc(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_scd(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sd(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sdl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sdr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sh(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sll(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sllv(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_slt(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_slti(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sltiu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sltu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sra(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_srav(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_srl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_srlv(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sub(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_subu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_swl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_swr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sync(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_syscall(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_teq(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_teqi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tge(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tgei(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tgeiu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tgeu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tlt(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tlti(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tltiu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tltu(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tne(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tnei(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_xor(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_xori(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc0f(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc0fl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc0t(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc0tl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dmfc0(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dmtc0(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mfc0(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mtc0(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_cache(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tlbp(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tlbr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tlbwi(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_tlbwr(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_absf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_addf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc1f(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc1fl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc1t(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_bc1tl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ceill(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ceilw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_cfc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ctc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_cvtd(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_cvtl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_cvts(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_cvtw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_divf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dmfc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_dmtc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_fcompare(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_floorl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_floorw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_ldc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_lwc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mfc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_movf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mtc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_mulf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_negf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_roundl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_roundw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sdc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_sqrtf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_subf(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_swc1(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_truncl(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}

void instr_truncw(R4300iInstructionWrapper *instr, R4300i *cpu, word *ram) {
	
}
