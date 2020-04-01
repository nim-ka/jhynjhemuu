#include <iostream>
#include <string>
#include <queue>

#include "utils.hpp"

std::queue<Message> messageQueue;

bool update_message_queue() {
	if (messageQueue.empty()) {
		return false;
	}

	Message msg = messageQueue.front();
	messageQueue.pop();

	switch (msg.type) {
		case MSG_ERROR:
			std::cerr << "\e[1m\e[31m[ERROR] \e[0m" << msg.content << std::endl;
			exit(1);
			break;

		case MSG_WARN:
			std::cerr << "\e[1m\e[33m[WARNING] \e[0m" << msg.content << std::endl;
			break;

		case MSG_INFO:
			std::cout << "\e[1m[INFO] \e[0m" << msg.content << std::endl;
			break;
	}

	return !messageQueue.empty();
}

void error(const std::string &str) {
	messageQueue.push({ MSG_ERROR, str });
}

void warn(const std::string &str) {
	messageQueue.push({ MSG_WARN, str });
}

void info(const std::string &str) {
	messageQueue.push({ MSG_INFO, str });
}

void nop(const std::string &str) {}
