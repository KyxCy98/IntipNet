#include <iostream>
#include "message.hpp"
#define RESET "\e[37m"
#define GREEN "\e[32m"
#define RED "\e[31m"
#define BLUE "\e[34m"
 
void msgHelp() {
	// log.debug("User gives output 'intip == `help`' and it is executed successfully!");
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

namespace Message {
	namespace Public {
		void MenuSql() {
			std::cout << "testing" << std::endl;
		}
	}
	
	namespace Error {
		void ErrorInput() {
			std::cout << "\n[-] Unknown command" << std::endl;
			std::cout << "[-] Usage: help [options]\n" << std::endl;
		}
	}
	
}
