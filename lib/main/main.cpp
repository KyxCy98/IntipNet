#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include "logger.hpp"
#include "message.hpp"
#include "banner.hpp"
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

class Start {
	public:
		Logger log{"debug/debug.log"};
		Output opt;

		void scan(const char* shellcmd) {
			std::string cmd = std::string(shellcmd) + " > /dev/null 2>&1";
			system(cmd.c_str());
			log.debug(shellcmd);
			log.info("successfully executed shell");
		}

		//
		// QL = SQL
		//
		void QLDefault() {
			log.info("'QLDefault' successfully executed!.");
			std::string input;
			std::cout << "input target# ";
			if (!(std::getline(std::cin, input))) return;

			if (input.empty()) {
				log.warn("user did not provide correct input");
				opt.warn("input cannot be empty!");
				return;
			}

			log.debug("user entered input" + input);
			scan(("nmap " + input).c_str());
		}
		
		void QLStart() {
			std::string input;
			std::cout << "[" << "\e[31m" << "root" << "\e[37m" <<"@intip] Sql# ";
			std::getline(std::cin, input);

			if (input == "1") {
				log.info("tes executed!");
			}
		}
};

int main() {
	Logger log("debug/debug.log");
	Output opt;
	Start shell;
	log.info("Started IntipNet");
	shell.scan("nmap");
	std::string intip;

	system("clear");
	log.debug("The system successfully cleared the terminal.");
	// system("rm -fr debug");
	// log.info("System has been removed old debug!");

	checkconnection();

	banner();
	log.debug("'banner()' function was called successfully");
	std::cout << "\t\t\tWelcome to IntipNet!\n";
	std::cout << "\t\t\tto use IntipNet type help or start!\n\n";

	while (true) {

		std::cout << "[" << "\e[31m" << "root" << "\e[37m" <<"@intip]~# ";
		std::getline(std::cin, intip);

		if (intip == "help") {
			log.debug("User gives output 'intip == `help`' and it is executed successfully!");
			msgHelp();
			// intel(BLUE, "CMD\n");
			// intel(RED, "Option:\n");
			// std::cout << "help <option> — to display the help menu specifically\n";
			// std::cout << "start <option> — to perform scanning or run scripts\n\n";
			// intel(RED, "Scanning:\n");
			// std::cout << "sql — to display menu sql test scan\n";
			// std::cout << "sub — subdomain enumeration\n";
			// std::cout << "xss — to enumerate scan xss\n\n";
			// std::cout << ""
		} else if (intip == "help sql") {
			log.debug("User gives output 'intip == `help sql`' and it is executed successfully!");
			intel(BLUE, "CMD\n");
			intel(RED, "Description:\n");
			std::cout << "SQL Injection — Using popular tools to detect more accurately using the 'sqlmap' tool\n";
			intel(RED, "Option:\n");
			std::cout << "sql start — start sql injection with standard method\n";
			std::cout << "sql dump — to dump database with standard method\n";
			std::cout << "sql custom — customize method\n\n";
	    } else if (intip == "sql") {
	    	shell.QLDefault();
		} else {
			opt.warn("you selected the wrong 'cmd' please use `help` to see the correct cmd!\n");
			log.debug("User entered wrong input, no matching output!");
		}
	}
}
