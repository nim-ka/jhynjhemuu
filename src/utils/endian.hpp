#pragma once

#include <cstdint>

class be_uint16_t {
    public:
        be_uint16_t(void): be_val_(0) {};

        be_uint16_t(const uint16_t &val): be_val_(__builtin_bswap16(val)) {};

        operator uint16_t(void) const;
    private:
        uint16_t be_val_ = 0;
} __attribute__((packed));

class be_uint32_t {
    public:
        be_uint32_t(void): be_val_(0) {};

        be_uint32_t(const uint32_t &val): be_val_(__builtin_bswap32(val)) {};

        operator uint32_t(void) const;
    private:
        uint32_t be_val_ = 0;
} __attribute__((packed));

class be_uint64_t {
    public:
        be_uint64_t(void): be_val_(0) {};

        be_uint64_t(const uint32_t &val): be_val_(__builtin_bswap64(val)) {};

        operator uint64_t(void) const;
    private:
        uint64_t be_val_ = 0;
} __attribute__((packed));
