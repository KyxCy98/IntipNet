#include <iostream>
#include "message.hpp"
#define RESET "\e[37m"
#define GREEN "\e[32m"
#define RED "\e[31m"
#define BLUE "\e[34m"
 
namespace Message {
	namespace Default {
		void msgHelp() {
			std::cout << BLUE << "CMD\n" << RESET << std::endl;
			std::cout << RED << "Option:\n" << RESET << std::endl;
			std::cout << "help <option> — to display the help menu specifically\n";
			std::cout << "start <option> — to perform scanning or run scripts\n\n";
			std::cout << RED << "Scanning:\n" << RESET << std::endl;
			std::cout << "port - scanning using nmap for bf port\n";
			std::cout << "subdo - enumeration subdomain" << std::endl;
			std::cout << "archive - retrieve all url for crawling\n" << std::endl;
			std::cout << RED << "System:\n" << RESET << std::endl;
			std::cout << "update - update tools to latest version" << std::endl;
		}
	}
	
	namespace Error {
		//
		// 1xx for error input
		//
		void ErrorInput() {
			std::cout << "\n[-] [Code: E-101] Unknown command" << std::endl;
			std::cout << "[-] [Code: E-104] Usage: help [options]\n" << std::endl;
		}

		//
		// 2xx error connection
		//
		void ErrorConnection() {
			std::cout << "\n[-] [Code: E-204] Connection is unstable, please check your connection before running it" << std::endl;
			std::cout << "[-] [Code: E-204] Did you use proxy?" << std::endl;
		}

		void Global() {
			std::cout << "\n[-] [Code: E-301] This is a global message in the script, stating that the script cannot run the module. Please double-check before running the script." << std::endl;
		}
	}

	namespace Updater {
		void UpdateML() {
			std::cout << "This script does not support ML yet" << std::endl;
		}

		void UpdateSC() {
			std::cout << "Next Update, maybe it will be added :)" << std::endl;
		}
	}
	
	// message section
	namespace Exit {
		void ExitMSG() {
			std::cout << "Thank you for using me:}" << std::endl;
		}
	}
}
