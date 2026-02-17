#include "engine.hpp"
#include <cstdlib>

namespace Engine {
	int Command::exec(const std::string& cmd) {
		return std::system(cmd.c_str());
	}

	int Command::exec_silent(const std::string& cmd) {
		#ifdef _WIN32
			return std::system((cmd + " > nul 2>&1").c_str());
		#else
			return std::system((cmd + " > /dev/null 2>&1").c_str());
		#endif
	}

	int Command::exec_check(const std::string& cmd) {
		int ret = exec(cmd);
		return ret == 0;
	}
}
