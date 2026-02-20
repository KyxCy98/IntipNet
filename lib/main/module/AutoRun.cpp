#include "AutoRun.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#define RESET "\e[37m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define RED "\e[31m"

namespace Auto {
    namespace Exec {
        std::string getTime() {
            std::time_t now = std::time(0);
            char* dt = std::ctime(&now);
            std::string timeStr(dt);
            if (!timeStr.empty() && timeStr.back() == '\n') timeStr.pop_back();
            return timeStr;
        }
        
        //
        // portscanning section
        //
        void PortScanner::start(const std::string& target) {
            std::cout << "\n      PortScanning starting on: " << target << std::endl;
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This uses a faster payload or CLI and depends on the host being \e[32mup\e[37m or \e[31mdown\e[37m." << std::endl;
            std::cout << "      This process using \e[34mnmap\e[37m payload..." << std::endl;

            std::string cmd = "nmap -vv -Pn --open -p 1-5000 --top-ports 1000 -T5 " + target + " > /dev/null 2>&1";
            std::system(cmd.c_str());
        }

        void PortScanner::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << "\n" << std::endl;
        }
        //
        // end section

        //
        // subdomain enumeration
        //
        void SubdomainEnum::start(const std::string& target) {
            std::cout << "\n      Subdomain enumeration for: " << target << std::endl;
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This process using " << BLUE << "Subfinder" << RESET << " and using " << BLUE << "Httpx" << RESET << " for filtering status code" << std::endl;

            std::string subfinder = "subfinder -d " + target + " -silent";
            std::system((subfinder + " -o " + target + "_tmp.tmp > /dev/null 2>&1").c_str());

            std::cout << "      Scanning " << GREEN << "Subfinder " << RESET << "done.. checking status code using " << BLUE << "Httpx" << RESET << std::endl;
            std::string httpx = "cat " + target + "_tmp.tmp | httpx -sc -o " + target + "_sc.httpx > /dev/null 2>&1";
            std::system(httpx.c_str());

            std::cout << "      Clearing tmp file.. showing the result.." << std::endl;
            std::string clear = "rm *.tmp | cat " + target + "_sc.httpx";
            std::system(clear.c_str());
        }

        void SubdomainEnum::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << std::endl;
        }
        //
        // end section
        //
    }
}