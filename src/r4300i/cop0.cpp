#include "utils.hpp"
#include "r4300i.hpp"

R4300iCOP0::R4300iCOP0(R4300i *cpu) {
#ifdef DEBUG
	info("Initializing COP0");
#endif

	this->cpu = cpu;
}

word R4300iCOP0::virt_to_phys(word address) {
	if (address >= 0x80000000 && address < 0xc0000000) {
		return address & 0x1FFFFFFF;
	} else {
		// TODO: TLB

#ifdef DEBUG
	info("TLB lookup for address" + get_hex<word>(address));
#endif
	}
}
