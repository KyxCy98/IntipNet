#ifndef ENGINE
#define ENGINE

#include <string>

namespace Engine {
	class Command {
		public:
			static int exec(const std::string& cmd);
			static int exec_silent(const std::string& cmd);
			static int exec_check(const std::string& cmd);
	};
}

#endif
