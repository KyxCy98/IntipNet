#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include "nlohmann/json.hpp"
#include "logger.hpp"
#include <unordered_map>
#include "message.hpp"
#include "banner.hpp"
#include "engine.hpp"
#include "AutoRun.hpp"
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
		Message::Error::ErrorConnection();
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
		//
		// LOAD CONFIG
		//	
		std::string name;
		std::string desc;
		std::string shell;
		std::string author;
		std::string arg;
		
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
	    	std::ifstream f(ren);

	    	if (!f.is_open()) {
	    		log.warn("file template not found!");
	    		return;
	    	}

	    	try {
	    		json cfg = json::parse(f);
	    		name	= cfg.value("name", "null");
	    		desc	= cfg.value("desc", "null");
	    		shell   = cfg.value("shell", "null");
	    		author	= cfg.value("author", "null");
	    		arg		= cfg.value("arg", "null");
	    	} catch (json::exception& e) {
	    		log.warn("HIT -> " + std::string(e.what()));
	    	}
	    }		
};

int main() {
    // Resource
    Logger log("debug/debug.log");
    Start shell;
    std::string userInput;
    log.info("Started IntipNet");
    shell.scan("nmap");

    std::cout << "\033[2J\033[1;1H"; 
    log.debug("Terminal cleared successfully.");

    checkconnection();
    banner();
    log.debug("'banner()' called successfully");

    std::cout << "\t\t\tWelcome to IntipNet!\n";
    std::cout << "\t\t\tTo use IntipNet type 'help' or 'start'!\n\n";

	int check = std::system("python3 lib/main/engine/check.py"); // module check
	if (check != 0) {
    	return 1;
	}

    while (true) {
        std::cout << "[\033[31mroot\033[37m@intip]~# ";
        
        if (!std::getline(std::cin, userInput) || userInput == "exit" || userInput == "q") {
            log.info("User exited the session.");
			Message::Exit::ExitMSG();
            break;
        }

        // Command Handling
        if (userInput == "help" || userInput == "ls") {
            log.debug("Executing help command");
            Message::Default::msgHelp();
        } 
        else if (userInput == "help sql") {
            log.debug("Executing help sql command");
		}
        else if (userInput == "port") {
			std::string target;
			std::cout << "[\033[31mroot\033[37m@intip]~/target# ";

			std::getline(std::cin, target);

			Auto::Exec::PortScanner::start(target);
			Auto::Exec::PortScanner::end();
        }
		else if (userInput == "subdo") {
			std::string target;
			std::cout << "[\033[31mroot\033[37m@intip]~/target# ";

			std::getline(std::cin, target);

			Auto::Exec::SubdomainEnum::start(target);
			Auto::Exec::SubdomainEnum::end();
		}
     	else if (userInput == "clear") {
            Engine::Command::exec("clear");
            banner();
        } 
        else if (!userInput.empty()) {
            Message::Error::ErrorInput();
            log.debug("Unknown input: " + userInput);
        }
    }

    return 0;
}
