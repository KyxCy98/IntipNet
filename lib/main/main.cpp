#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include "nlohmann/json.hpp"
#include "logger.hpp"
#include "message.hpp"
#include "banner.hpp"
#include "engine.hpp"
#define RESET "\e[37m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define RED "\e[31m"

using json = nlohmann::json;

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
	private:
		std::string name;
		
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
		// Json for template
		//
		void render(const char* ren) {
			// std::string name = cfg["name"];
			std::ifstream f(ren);
			log.debug("called ifstream");
			log.debug(ren);
			json cfg = json::parse(f);
			name = cfg["name"];
			log.debug("called string 'name' in config templates");

			std::cout << name << std::endl;
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
			log.info("'QLStart' successfully executed!.");
			std::string input;
			std::cout << "The script asks you to enter the tool options you want to use to check for SQL injection." << std::endl;
			std::cout << "1. Use tool sqlmap for testing" << std::endl;
			std::cout << "2. Use custom tools for testing\n" << std::endl;
			std::cout << "[" << "\e[31m" << "root" << "\e[37m" <<"@intip] Sql# ";
			std::getline(std::cin, input);

			if (input == "1") {
				log.info("Input user successfully executed!");
				std::string target;
				std::cout << "Enter the template to use this:)" << std::endl;
				std::cout << "1. Normally template\n2. Custom template\n3. With ML Bypass(Beta)" << std::endl;
				std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip] sqlmap# ";
				std::getline(std::cin, target);

				if (target == "1") {
					render("templates/config.json");
				}
					
			} else if (input == "2") {
				
			} else {
				
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
	// Engine::Command::exec("ls");

	system("clear");
	log.debug("The system successfully cleared the terminal.");

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
		} else if (intip == "help sql") {
			log.debug("User gives output 'intip == `help sql`' and it is executed successfully!");
			showSql();
	    } else if (intip == "sql") {
	    	shell.QLDefault();
		} else if (intip == "sql start") {
			shell.QLStart();
		} else {
			opt.warn("you selected the wrong 'cmd' please use `help` to see the correct cmd!\n");
			log.debug("User entered wrong input, no matching output!");
		}
	}
}
