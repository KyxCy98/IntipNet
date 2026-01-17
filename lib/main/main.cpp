#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "module/logger.hpp"
#define RESET "\e[37m"
#define BIRU "\e[34m"
#define HIJAU "\e[32m"
#define MERAH "\e[31m"

void intel(const char* warna, const char* teks) {
	std::cout << warna << teks << RESET << std::endl;
}

void checkconnection() {
	int check = system("ping -c 4 google.com > /dev/null 2>&1");
	if (check == 0) {
		std::cout << "Connection stabil!" << std::endl;
	} else {
		std::cout << "Connection refushed!" << std::endl;
	}
}

class Output {
	public:
		void warn(const char* text) {
			std::cout << "[WRN] " << text << std::endl;
		}

		void info(const char* text) {
			std::cout << "[INF] " << text << std::endl;
		}

		void debug(const char* text) {
			std::cout << "[DBG] " << text << std::endl;
		}
};

int main() {
	Logger log("debug/debug.log");

	log.info("Started IntipNet");
	std::string intip;
	Output opt;

	system("clear");


	checkconnection();

	// system("clear");
	
	std::cout << R"(
                                                                              
                                                                              
      L.                                    L.                     ,;         
  t   EW:        ,ft          t   t         EW:        ,ft       f#i          
  Ej  E##;       t#E GEEEEEEELEj  ED.       E##;       t#E     .E#t  GEEEEEEEL
  E#, E###t      t#E ,;;L#K;;.E#, E#K:      E###t      t#E    i#W,   ,;;L#K;;.
  E#t E#fE#f     t#E    t#E   E#t E##W;     E#fE#f     t#E   L#D.       t#E   
  E#t E#t D#G    t#E    t#E   E#t E#E##t    E#t D#G    t#E :K#Wfff;     t#E   
  E#t E#t  f#E.  t#E    t#E   E#t E#ti##f   E#t  f#E.  t#E i##WLLLLt    t#E   
  E#t E#t   t#K: t#E    t#E   E#t E#t ;##D. E#t   t#K: t#E  .E#L        t#E   
  E#t E#t    ;#W,t#E    t#E   E#t E#ELLE##K:E#t    ;#W,t#E    f#E:      t#E   
  E#t E#t     :K#D#E    t#E   E#t E#L;;;;;;,E#t     :K#D#E     ,WW;     t#E   
  E#t E#t      .E##E    t#E   E#t E#t       E#t      .E##E      .D#;    t#E   
  E#t ..         G#E     fE   E#t E#t       ..         G#E        tt     fE   
  ,;.             fE      :   ,;.                       fE                :   
                   ,                                     ,                    
	 )";
	std::cout << "\t\t\tWelcome to IntipNet!\n";
	std::cout << "to use IntipNet type help or start!";
	// opt.warn("hello world?!");
	// opt.debug("debug", "tes");
	intel(MERAH, "Tes");

	std::cout << "[root@intip]~# ";
	std::getline(std::cin, intip);

	if (intip == "1") {
		std::cout << "intip";
	} else if (intip == ".help") {
		
	} else {
		std::cout << "salah!";
	}
}
