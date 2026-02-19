#include "AutoRun.hpp"
#include <iostream>
#include <string>

namespace Auto {
    namespace Exec {
        void PortScanner::start(const std::string& target) {
            std::cout << "[+] PortScanner starting on: " << target << std::endl;
        }

        void PortScanner::end() {
            std::cout << "end scanning" << std::endl;
        }
    }
}