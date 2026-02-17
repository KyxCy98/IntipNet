#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

class Logger {
	public:
		Logger(const std::string& filename);
		~Logger();

		void debug(const std::string& msg);
		void info(const std::string& msg);
		void warn(const std::string& msg);
		void critical(const std::string& msg);

	private:
		std::ofstream file;
		void write(const std::string& level, const std::string& msg);
};

#endif
