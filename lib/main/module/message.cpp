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
			std::cout << "sql — to display menu sql test scan\n";
			std::cout << "sub — subdomain enumeration\n";
			std::cout << "xss — to enumerate scan xss\n\n";
		}

		void showSql() {
			std::cout << BLUE << "CMD\n" << RESET << std::endl;
			std::cout << RED << "Description:\n" << RESET << std::endl;
			std::cout << "SQL Injection - Using popular tools to detect more accurately using 'sqlmap' tools\n";
			std::cout << RED << "Option:\n" << RESET << std::endl;
 			std::cout << "sql start — start sql injection with standard method\n";
			std::cout << "sql dump — to dump database with standard method\n";
			std::cout << "sql custom — customize method\n\n";
		}
	}
	
	namespace Sql {
		void Sql() {
			std::cout << "\n[!] Entering SQL Injection Module" << std::endl;
			std::cout << "[?] Select testing method:\n" << std::endl;
			std::cout << "	(1) Sqlmap Integration" << std::endl;
			std::cout << "	(2) Custom payload inject\n" << std::endl;
		}

		void Menu() {
			std::cout << "\n[!] Entering method" << std::endl;
			std::cout << "[?] Select method:\n" << std::endl;
			std::cout << "	(1) Default Method" << std::endl;
			std::cout << "	(2) Custom Method" << std::endl;
			std::cout << "	(3) With ML Method\n" << std::endl;
		}

		void Error() {
			std::cout << "Sqlmap not installed!" << std::endl;
		}

		void dumpSlq() {
			std::cout << "\n[!] Entering Dumping Module" << std::endl;
			std::cout << "[?] Select method: \n" << std::endl;
			std::cout << "	(1) By database dump" << std::endl;
			std::cout << "	(2) Dump All" << std::endl;
			std::cout << "	(3) Dump from specific tables" << std::endl;
			std::cout << "	(4) Dump only table" << std::endl;
			std::cout << "	(5) Dump by automatic" << std::endl;
		}
	}

	// section xss

	namespace Xss {
		void Xss() {
			std::cout << '\n' << std::endl;
		}

		void Menu() {
    		std::cout << BLUE << "CMD\n" << RESET << std::endl;
    		std::cout << RED << "Description:\n" << RESET << std::endl;
    		std::cout << "Cross-Site Scripting (XSS) - Advanced parameter analysis and scanning using 'dalfox'\n";
    		std::cout << RED << "Option:\n" << RESET << std::endl;
    		std::cout << "xss url    — scan a single target URL for XSS vulnerabilities\n";
		    std::cout << "xss pipe   — scan targets from list/stdout (pipeline mode)\n";
    		std::cout << "xss sxss   — blind/stored XSS scanning with custom header/payload\n\n";
		}

		void Warn() {
			std::cout << "\nHEY! Ensure that Dalfox has been installed before conducting penetration testing on the target website." << std::endl;
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
	
}
