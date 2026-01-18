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
