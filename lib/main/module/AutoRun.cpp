#include "AutoRun.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include <stdexcept>
#include <memory>
#include <cstdio>
#define RESET "\e[37m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define RED "\e[31m"

bool safe(const std::string& input) {
    if (input.empty()) return false;
    std::string bidden = ";&|`$>{}[]()";
    for (char c : input) {
        if (bidden.find(c) != std::string::npos) return false;
    }
    return true;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

namespace Auto {
    namespace Exec {
        std::string getTime() {
            std::time_t now = std::time(0);
            char* dt = std::ctime(&now);
            std::string timeStr(dt);
            if (!timeStr.empty() && timeStr.back() == '\n') timeStr.pop_back();
            return timeStr;
        }

        // PortScanner Section
        void PortScanner::start(const std::string& target) {
            if (!safe(target)) return;
            std::cout << "\n      PortScanning starting on: " << target << std::endl;
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This uses a faster payload or CLI and depends on the host being \e[32mup\e[37m or \e[31mdown\e[37m." << std::endl;
            std::cout << "      This process using \e[34mnmap\e[37m payload..." << std::endl;

            std::string cmd = "nmap -vv -Pn --open -p 1-5000 --top-ports 1000 -T5 " + target + " -oX " + target + ".xml > /dev/null 2>&1";
            std::system(cmd.c_str());
        }

        void PortScanner::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << "\n" << std::endl;
        }

        // Subdomain Enumeration Section
        void SubdomainEnum::start(const std::string& target) {
            if (!safe(target)) return;
            std::cout << "\n      Subdomain enumeration for: " << target << std::endl;
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This process using " << BLUE << "Subfinder" << RESET << " and using " << BLUE << "Httpx" << RESET << " for filtering status code" << std::endl;

            std::system(("subfinder -d " + target + " -silent -o " + target + "_tmp.tmp > /dev/null 2>&1").c_str());

            std::cout << "      Scanning " << GREEN << "Subfinder " << RESET << "done.. checking status code using " << BLUE << "Httpx" << RESET << std::endl;
            std::system(("cat " + target + "_tmp.tmp | httpx -sc -o " + target + "_sc.httpx > /dev/null 2>&1").c_str());

            std::cout << "      Clearing tmp file.. showing the result..\n" << std::endl;
            std::system(("rm " + target + "_tmp.tmp 2>/dev/null | cat " + target + "_sc.httpx").c_str());
        }

        void SubdomainEnum::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << std::endl;
        }

        // Archive Section
        void Archive::start(const std::string& target) {
            if (!safe(target)) return;
            std::cout << "\n      Archive checking for: " << target << std::endl;
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This process using " << BLUE << "Wayback Machine" << RESET << " and using " << BLUE << "Httpx\n" << RESET << std::endl;

            std::system(("python3 lib/main/engine/archive.py -u " + target + " -o --timeout 30 --retries 5 --backoff 2").c_str());

            std::cout << "\n      Archive scanning done.. running httpx and filtering status code" << std::endl;
            std::system(("cat wayback-" + target + ".txt | httpx -sc -o " + target + "_sc.httpx > /dev/null 2>&1").c_str());

            std::system(("mkdir -p tmp/" + target).c_str());
            
            std::vector<std::string> codes = {"200", "302", "403", "404"};
            for(const auto& sc : codes) {
                std::string cmd = "grep '" + sc + "' " + target + "_sc.httpx > tmp/" + target + "/" + sc + ".tmp 2>/dev/null";
                std::system(cmd.c_str());
            }

            std::cout << "      Summary scanning saved at: " << std::endl;
        }

        void Archive::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << std::endl;            
        }

        // dns record checking
        void Dns::start(const std::string& target) {
            if (!safe(target)) {
                return;
            }

            std::cout << "\n      Dns lookup for: " << target << std::endl; 
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This process using module " << BLUE << "dig" << RESET << std::endl;

            std::string types[] = {"A", "AAA", "MX", "NS", "TXT"};

            for (const std::string& type : types) {
                std::cout << RED << type << RESET << " Records\n" << std::endl;

                std::string cmd = "dig " + target + " " + type + " +short";
                std::string output = exec(cmd.c_str());

                if (output.empty()) {
                    std::cout << " (No Record found)" << std::endl;
                } else {
                    std::cout << output << std::endl;
                }
            }
        }

        void Whois::start(const std::string& target) {
            if (!safe(target)) {
                return;
            }

            std::cout << "\n      Whois lookup for: " << target << std::endl;
            std::cout << "      Scanning started: " << getTime() << std::endl;
            std::cout << "      This process using module " << BLUE << "whois\n" << RESET << std::endl;

            std::string cmd = "whois " + target;
            std::system(cmd.c_str());
        }

        void Whois::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << std::endl;
        }

        void Dns::end() {
            std::cout << "\n      End scanning. finished at: " << getTime() << std::endl;            
        }

        void Update::update() {
            std::cout << "\n      Checking update system" << std::endl;
            std::system("git pull");
        }
    }
}