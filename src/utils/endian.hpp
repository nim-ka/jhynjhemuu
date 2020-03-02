#pragma once

#include <cstdint>

class be_uint16_t {
	public:
		be_uint16_t(void);

		be_uint16_t(const uint16_t &val);

		operator uint16_t(void) const;
	private:
		uint16_t be_val_;
} __attribute__((packed));

class be_uint32_t {
	public:
		be_uint32_t(void);

		be_uint32_t(const uint32_t &val);

		operator uint32_t(void) const;
	private:
		uint32_t be_val_;
} __attribute__((packed));
