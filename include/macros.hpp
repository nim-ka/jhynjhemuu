#pragma once

#define WORD_FROM_BYTE_PTR(ptr) ((ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3])

#define LOWER_BYTE(x) ((hword)(x) & 0xFF)
#define UPPER_BYTE(x) ((hword)(x) >> 8)

#define LOWER_HWORD(x)	((word)(x) & 0xFFFF)
#define UPPER_HWORD(x)	((word)(x) >> 16)

#define LOWER_WORD(x)	((dword)(x) & 0xFFFFFFFF)
#define UPPER_WORD(x)	((dword)(x) >> 32)

#define LOWER_DWORD(x)	((qword)(x) & 0xFFFFFFFFFFFFFFFF)
#define UPPER_DWORD(x)	((qword)(x) >> 64)

#define SIGN_EXTEND_BYTE(x)	((hword)(x) | ((hword)(x & 0x80) * 0x1FE))
#define SIGN_EXTEND_HWORD(x)	((word)(x) | ((word)(x & 0x8000) * 0x1FFFE))
#define SIGN_EXTEND_WORD(x)	((dword)(x) | ((dword)(x & 0x80000000) * 0x1FFFFFFFE))

#define SIGN_EXTEND_HWORD_TWICE(x)	SIGN_EXTEND_WORD(SIGN_EXTEND_HWORD(x))
#define SIGN_EXTEND_BYTE_TWICE(x)	SIGN_EXTEND_HWORD(SIGN_EXTEND_BYTE(x))
#define SIGN_EXTEND_BYTE_THRICE(x)	SIGN_EXTEND_WORD(SIGN_EXTEND_HWORD(SIGN_EXTEND_BYTE(x)))
