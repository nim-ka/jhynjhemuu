#include <iomanip>
#include <string>

#include "utils.hpp"
#include "r4300i.hpp"

R4300iInstruction opcodeTable[] = {
	INSTR_NONE,	INSTR_NONE,	INSTR_J,	INSTR_JAL,	INSTR_BEQ,	INSTR_BNE,	INSTR_BLEZ,	INSTR_BGTZ,
	INSTR_ADDI,	INSTR_ADDIU,	INSTR_SLTI,	INSTR_SLTIU,	INSTR_ANDI,	INSTR_ORI,	INSTR_XORI,	INSTR_LUI,
	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_BEQL,	INSTR_BNEL,	INSTR_BLEZL,	INSTR_BGTZL,
	INSTR_DADDI,	INSTR_DADDIU,	INSTR_LDL,	INSTR_LDR,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,	INSTR_NONE,
	INSTR_LB,	INSTR_LH,	INSTR_LWL,	INSTR_LW,	INSTR_LBU,	INSTR_LHU,	INSTR_LWR,	INSTR_LWU,
	INSTR_SB,	INSTR_SH,	INSTR_SWL,	INSTR_SW,	INSTR_SDL,	INSTR_SDR,	INSTR_SWR,	INSTR_NONE,
	INSTR_LL,	INSTR_FLWC1,	INSTR_NONE,	INSTR_NONE,	INSTR_LLD,	INSTR_FLDC1,	INSTR_NONE,	INSTR_LD,
	INSTR_SC,	INSTR_FSWC1,	INSTR_NONE,	INSTR_NONE,	INSTR_SCD,	INSTR_FSDC1,	INSTR_NONE,	INSTR_SD
};

R4300iInstructionWrapper::R4300iInstructionWrapper(word value) {
	formats = new R4300iInstructionFormats();
	formats->value = value;

	word opcode = formats->r_format.opcode;

	instr = opcodeTable[opcode];

	if (instr == INSTR_NONE) {
		switch (opcode) {
			case OPC_SPECIAL:
				break;

			case OPC_REGIMM:
				break;

			case OPC_COP0:
				break;

			case OPC_COP1:
				break;

			default:
				std::stringstream stream;

				stream << "Unrecognized instruction: "
					<< std::setfill('0')
					<< std::setw(8)
					<< std::hex << value;

				error(stream.str());
		}
	}
}
