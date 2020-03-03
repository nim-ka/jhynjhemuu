#pragma once

#define WORD_FROM_BYTE_PTR(ptr) ((ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3])

#define LOWER_HWORD(x)	((word)(x) & 0xFFFF)
#define UPPER_HWORD(x)	((word)(x) >> 16)

#define LOWER_WORD(x)	((dword)(x) & 0xFFFFFFFF)
#define UPPER_WORD(x)	((dword)(x) >> 32)

#define LOWER_DWORD(x)	((qword)(x) & 0xFFFFFFFFFFFFFFFF)
#define UPPER_DWORD(x)	((qword)(x) >> 64)

#define SIGN_EXTEND_HWORD(x)	((word)(x) | ((word)(x & 0x8000) * 0x1FFFE))
#define SIGN_EXTEND_WORD(x)	((dword)(x) | ((dword)(x & 0x80000000) * 0x1FFFFFFFE))
