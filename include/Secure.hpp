#ifndef SECURE_HPP
#define SECURE_HPP
#include <string>

bool sanitize(const std::string& input);
void secureInput(const std::string& cmd);
#endif