#include "logger.hpp"
#include <iostream>
#include <ctime>
#include <cstring>

Logger::Logger(const std::string& filename)
{
	file.open(filename, std::ios::app);
}

Logger::~Logger() {
	if (file.is_open()) {
		file.close();
	}
}

void Logger::write(const std::string& level, const std::string& msg) {
	if (!file.is_open()) return;

	std::time_t now = std::time(nullptr);
	char* timeStr = std::ctime(&now);
	timeStr[strlen(timeStr) - 1] = '\0';

	file << "[" << timeStr << "] "
		 << "[" << level << "] "
		 << msg << std::endl;
};

void Logger::debug(const std::string& msg) { 
	write("DEBUG", msg);
}

void Logger::info(const std::string& msg) {
	write("INFO", msg);
}

void Logger::warn(const std::string& msg) {
	write("WARN", msg);
}

void Logger::critical(const std::string& msg) {
	write("CRITICAL", msg);
}
