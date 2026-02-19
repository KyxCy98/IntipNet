#ifndef AUTORUN_HPP
#define AUTORUN_HPP
#include <string>

namespace Auto {
    namespace Exec {
        class PortScanner {
        public:
            static void start(const std::string& target); 
            static void end();
        };
    }
}

#endif