#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "types.hpp"
#include "macros.hpp"

enum MessageType {
	MSG_ERROR,
	MSG_WARN,
	MSG_INFO
};

struct Message {
	MessageType type;
	std::string content;
};

template <typename T> std::string get_hex(T num) {
	std::stringstream stream;

	stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << +num;

	return stream.str();
}

bool update_message_queue();

void error(const std::string &str);
void warn(const std::string &str);
void info(const std::string &str);

void nop(const std::string &str);

#ifdef DEBUG
#define debug_error	error
#define debug_warn	warn
#define debug_info	info
#else
#define debug_error	nop
#define debug_warn	nop
#define debug_info	nop
#endif
