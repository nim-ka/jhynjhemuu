#include <cstdint>

class be_uint16_t {
	public:
		be_uint16_t(void) : be_val_(0) {}

		be_uint16_t(const uint16_t &val) : be_val_(__builtin_bswap16(val)) {}

		operator uint16_t(void) const {
			return __builtin_bswap16(be_val_);
		}
	private:
		uint16_t be_val_;
} __attribute__((packed));

class be_uint32_t {
	public:
		be_uint32_t(void) : be_val_(0) {}

		be_uint32_t(const uint32_t &val) : be_val_(__builtin_bswap32(val)) {}

		operator uint32_t(void) const {
			return __builtin_bswap32(be_val_);
		}
	private:
		uint32_t be_val_;
} __attribute__((packed));
