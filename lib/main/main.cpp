#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "module/logger.hpp"
#include "module/banner.hpp"
#define RESET "\e[37m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define RED "\e[31m"

void intel(const char* color, const char* text) {
	std::cout << color << text << RESET << std::endl;
}

void checkconnection() {
	int check = system("ping -c 4 google.com > /dev/null 2>&1");
	if (check == 0) {
		std::cout << "stable connection!" << std::endl;
	} else {
		std::cout << "connection is unstable, please check the connection before continuing to use this script!\n" << std::endl;
		return;
	}
}

class Output {
	public:
		void warn(const char* text) {
			std::cout << "[" << "\e[31m" << "WRN" << "\e[37m" << "] " << text << std::endl;
		}

		void info(const char* text) {
			std::cout << "[" << "\e[32m" << "INF" << "\e[37m" << "] " << text << std::endl;
		}

		void debug(const char* text) {
			std::cout << "[" << "\e[34m" << "DBG" << "\e[37m" << "] " << text << std::endl;
		}
};

int main() {
	Logger log("debug/debug.log");

	log.info("Started IntipNet");
	std::string intip;
	Output opt;

	system("clear");
	log.debug("The system successfully cleared the terminal.");


	checkconnection();

	banner();
	log.debug("'banner()' function was called successfully");
	std::cout << "\t\t\tWelcome to IntipNet!\n";
	std::cout << "\t\tto use IntipNet type help or start!\n\n";

	while (true) {

		std::cout << "[" << "\e[31m" << "root" << "\e[37m" <<"@intip]~# ";
		std::getline(std::cin, intip);

		if (intip == "help") {
			intel(BLUE, "CMD\n");
			intel(RED, "Option:\n");
			std::cout << "help <option> — to display the help menu specifically\n";
			std::cout << "start <option> — to perform scanning or run scripts\n\n";
			intel(RED, "Scanning:\n");
			std::cout << "sql — to display menu sql test scan\n";
			std::cout << "sub — subdomain enumeration\n";
			std::cout << "xss — to enumerate scan xss\n\n";
			// std::cout << ""
		} else if (intip == "help sql") {
			intel(BLUE, "CMD\n");
			intel(RED, "Description:\n");
			std::cout << "SQL Injection — Using popular tools to detect more accurately using the 'sqlmap' tool\n";
			intel(RED, "Option:\n");
			std::cout << "sql start — start sql injection with standard method\n";
			std::cout << "sql dump — to dump database with standard method\n";
			std::cout << "sql custom — customize method\n\n";
		} else {
			opt.warn("you selected the wrong 'cmd' please use `help` to see the correct cmd!\n");
			log.debug("User entered wrong input, no matching output!");
		}
	}
}
