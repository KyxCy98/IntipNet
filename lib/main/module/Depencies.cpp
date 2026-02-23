#include "Depencies.hpp"
#include <iostream>
#include <vector>
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
                    std::cout << "modue not installed" << std::endl;
                    break;
                }
            }
        }
    }
}