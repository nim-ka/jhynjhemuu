#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "types.hpp"
#include "macros.hpp"

template <typename T> std::string get_hex(T num);

void error(const std::string &str);
void warn(const std::string &str);
void info(const std::string &str);
