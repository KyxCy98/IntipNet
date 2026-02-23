#ifndef AUTORUN_HPP
#define AUTORUN_HPP

#include <string>

namespace Auto {
    namespace Exec {
        // Base class untuk mendukung polimorfisme & memory management
        class Scanner {
        public:
            virtual ~Scanner() = default;
            virtual void start(const std::string& target) = 0;
            virtual void end() = 0;
        };

        class PortScanner : public Scanner {
        public:
            void start(const std::string& target) override;
            void end() override;
        };

        class SubdomainEnum : public Scanner {
        public:
            void start(const std::string& target) override;
            void end() override;
        };

        class Archive : public Scanner {
        public:
            void start(const std::string& target) override;
            void end() override;
        };

        class Update {
        public:
            static void update();
        };
    }
}

#endif