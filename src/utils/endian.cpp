#include <cstdint>

#include "utils.hpp"

be_uint16_t::operator uint16_t(void) const {
	return __builtin_bswap16(be_val_);
}

be_uint32_t::operator uint32_t(void) const {
	return __builtin_bswap32(be_val_);
}
