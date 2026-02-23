#include "Depencies.hpp"
#include "logger.hpp"
#include <iostream>
#include <vector>

Logger log("debug/debug.log");

bool exists(const std::string& input) {
    std::string check = "which " + input + " > /dev/null 2>&1";
    return (std::system(check.c_str()) == 0);
}

namespace __MODULE__ {
    namespace __CHECK__ {
        void check_requirement() {
            std::vector<std::string> module = {"etst", "nmap", "subfinder", "httpx", "python"};

            for (const auto& t : module) {
                if (!exists(t)) {
                    std::string warn = "module not installed please install manually or using script installer: " + t;

                    log.critical(warn);
                    break;
                }
            }
        }
    }
}