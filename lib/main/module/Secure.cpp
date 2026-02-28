#include "Secure.hpp"
#include <iostream>
#include <string>
#include "logger.hpp"

static Logger log("debug/security.log");

bool sanitize(const std::string& input) {
    std::string forbidden = ";&|`$><{}[]()";

    for (char c : input) {
        if (forbidden.find(c) != std::string::npos) {
            return false;
        }
    }
    return true;
}

void secureInput(const std::string& cmd) {
    if (!sanitize(cmd)) {
        log.warn("warning code, code dangerous has been sanitize!");
        return;
    }

}