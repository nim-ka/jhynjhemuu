#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "types.hpp"
#include "macros.hpp"

template <typename T> std::string get_hex(T num) {
	std::stringstream stream;

	stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << num;

	return stream.str();
}

void error(const std::string &str);
void warn(const std::string &str);
void info(const std::string &str);
