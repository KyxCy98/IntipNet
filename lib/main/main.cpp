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
			Message::Sql::Sql();
			std::cout << "[" << "\e[31m" << "root" << "\e[37m" <<"@intip/module/sql] ~# ";
			std::getline(std::cin, input);

			if (input == "1") {
				log.info("Input user successfully executed!");
				std::string target;
				Message::Sql::Menu();
				std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sql] ~# ";
				std::getline(std::cin, target);

				if (target == "1") {
					std::string target;
					std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sql] ~/target# ";
					std::getline(std::cin, target);
					
					if (!target.empty()) {
						std::string cmd = "sqlmap -u " + target + "--batch --dbs --tamper=space2comment,between,default --hex --level 5 --risk 3 -v 3";

						log.info("running sqlmap with cli " + cmd);

						int result = Engine::Command::exec(cmd);

						if (result != 0) {
							Message::Sql::Error();
						}
					} else {
						Message::Error::ErrorInput();
					}
					
				} else if (input == "2") {
					std::string target;
					std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sql] ~/custom# ";
					std::getline(std::cin, target);

					if (!target.empty()) {
						std::string cmd;

						if (cmd.find("sqlmap") == std::string::npos) {
							cmd = "sqlmap " + target;

							log.info("Engime started!, successully called engine");

							int result = Engine::Command::Exec(cmd);

							if (result != 0) {
								int error = Message::Sql::Error();
								log.debug("Engine Hitting something.. " + error);
							}
							
						} else {
							cmd = target;
						}

						// Engine::Command::exec(cmd);
					} else {
						Message::Error::ErrorInput();
					}
					
				} else if (input == "3") {
					Message::Updater::UpdateML();
				}
					
			} else if (input == "2") {
				Message::Updater::UpdateSC();
			} else {
				Message::Error::ErrorInput();
			}
		}

		void QLdump() {
			std::string input;
			Message::Sql::dumpSql();
			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~# ";
			std::getline(std::cin, input);

			if (target == "1") {
				std::string target;
				std::string db;
				// log.info("\nPlease input the target")
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/target# ";
	 			// log.info("\nPlease input the database")
				std::getline(std::cin, input);
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/database# ";
				std::getline(std::cin, input);

				if (!target.empty) {
					std::string cmd = "sqlmap -u " + target + "--batch -D " + db + " --dump --risk 3 --level 5 --tamper=space2comment --thread 10 --random-agent"

					log.info("Engine started, successfully called function");
					
					int result = Engine::Command::Exec(cmd);

					if (result != 0) {
						int output = Message::Sql:Error();
						log.debug("Engine hitting something..." + output);
					}
					
				} else {
					Message::Error::ErrorInput();
					log.warn("Message::Error::ErrorInput(); : Warning user entered wrong output")
				}
				
			} else if (target == "2") {
				std::string target;
				std::string db;
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/target# ";
				std::getline(std::cin, input);
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/database# ";
				std::getline(std::cin, input);

				if (!target.empty) {
				
					std::string cmd = "sqlmap -u " + target + "--batch -D " + db + " --dump-all --risk 3 --level 5 --tamper=space2comment --thread 10 --random-agent"
				} else {
					Message::Error::ErrorInput();
				}
				
			} else if (target == "3") {
				std::string target;
				std::string db;
				std::string table;
				std::string column;
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/target# ";
				std::getline(std::cin, input);
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/database# ";
				std::getline(std::cin, input);
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/table# ";
				std::getline(std::cin, input);
	 			std::cout << "[" << "\e[31m" << "root" << "\e[37m" << "@intip/module/sqlDump] ~/column# ";
				std::getline(std::cin, input);

				if (!target.empty()) {
					std::string cmd = "sqlmap -u " + target + "--batch -D " + db + " -T " + table +  " -C " + column + " --risk 3 --level 5 --tamper=space2comment --thread 10 --random-agent"
				} else {
					Message::Error::ErrorInput();
				}
			}
		}
};

int main() {
	Logger log("debug/debug.log");
	// Output opt;
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
			Message::Default::msgHelp();
		} else if (intip == "help sql") {
			log.debug("User gives output 'intip == `help sql`' and it is executed successfully!");
			Message::Default::showSql();
	    } else if (intip == "sql") {
	    	shell.QLDefault();
		} else if (intip == "sql start") {
			shell.QLStart();
		} else {
			Message::Error::ErrorInput();
			log.debug("User entered wrong input, no matching output!");
		}
	}
}
