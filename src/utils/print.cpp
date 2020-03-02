#include <iostream>
#include <string>

#include "utils.hpp"

void error(const std::string &str) {
	std::cerr << "\e[1m\e[31m[ERROR] \e[0m" << str << std::endl;
	exit(1);
}

void warn(const std::string &str) {
	std::cerr << "\e[1m\e[33m[WARNING] \e[0m" << str << std::endl;
}

void info(const std::string &str) {
	std::cout << "\e[1m[INFO] \e[0m" << str << std::endl;
}
