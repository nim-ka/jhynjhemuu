#pragma once

#define COP1 \
	(((union { \
		word x: 6; \
		word y: 2; \
	}) 0x44).x)

#define FPU_CODE_BC 8
#define FPU_CODE_S 16
#define FPU_CODE_D 17
#define FPU_CODE_W 20
#define FPU_CODE_L 21

#define VIRT_TO_PHYS(x) (x & ~0x80000000)
#define PHYS_TO_VIRT(x) (x | 0x80000000)
