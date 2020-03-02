#pragma once

// screw this and replace with tlb stuff eventually
#define VIRT_TO_PHYS(x) ((x) & ~0x80000000)
#define PHYS_TO_VIRT(x) ((x) | 0x80000000)

#define LOWER_HWORD(x)	((x) & 0xFFFF)
#define UPPER_HWORD(x)	((x) >> 16)

#define LOWER_WORD(x)	((x) & 0xFFFFFFFF)
#define UPPER_WORD(x)	((x) >> 32)

#define SIGN_EXTEND_HWORD(x)	((word)(x) | ((word)(x & 0x8000) * 0x1FFFE))
#define SIGN_EXTEND_WORD(x)	((dword)(x) | ((dword)(x & 0x80000000) * 0x1FFFFFFFE))
