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

	// system("clear");
	
	// std::cout << R"(
                                                                              
                                                                              
      // L.                                    L.                     ,;         
  // t   EW:        ,ft          t   t         EW:        ,ft       f#i          
  // Ej  E##;       t#E GEEEEEEELEj  ED.       E##;       t#E     .E#t  GEEEEEEEL
  // E#, E###t      t#E ,;;L#K;;.E#, E#K:      E###t      t#E    i#W,   ,;;L#K;;.
  // E#t E#fE#f     t#E    t#E   E#t E##W;     E#fE#f     t#E   L#D.       t#E   
  // E#t E#t D#G    t#E    t#E   E#t E#E##t    E#t D#G    t#E :K#Wfff;     t#E   
  // E#t E#t  f#E.  t#E    t#E   E#t E#ti##f   E#t  f#E.  t#E i##WLLLLt    t#E   
  // E#t E#t   t#K: t#E    t#E   E#t E#t ;##D. E#t   t#K: t#E  .E#L        t#E   
  // E#t E#t    ;#W,t#E    t#E   E#t E#ELLE##K:E#t    ;#W,t#E    f#E:      t#E   
  // E#t E#t     :K#D#E    t#E   E#t E#L;;;;;;,E#t     :K#D#E     ,WW;     t#E   
  // E#t E#t      .E##E    t#E   E#t E#t       E#t      .E##E      .D#;    t#E   
  // E#t ..         G#E     fE   E#t E#t       ..         G#E        tt     fE   
  // ,;.             fE      :   ,;.                       fE                :   
                   // ,                                     ,                    
	 // )";

	banner();
	log.debug("'banner()' function was called successfully");
	std::cout << "\t\t\tWelcome to IntipNet!\n";
	std::cout << "\t\tto use IntipNet type help or start!\n\n";
	// opt.warn("hello world?!");
	// opt.debug("debug", "tes");
	// intel(MERAH, "Tes");

	while (true) {

		std::cout << "[" << "\e[31m" << "root" << "\e[37m" <<"@intip]~# ";
		std::getline(std::cin, intip);

		if (intip == "help") {
			std::cout << "CMD\n\n";
			std::cout << "help <option> — to display the help menu specifically\n";
			std::cout << "start <option> — to perform scanning or run scripts\n";
			// std::cout << ""
		} else if (intip == ".help") {
		
		} else {
			opt.warn("you selected the wrong 'cmd' please use `help` to see the correct cmd!\n");
			log.debug("User entered wrong input, no matching output!");
		}
	}
}
