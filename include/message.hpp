#ifndef MESSAGE_HPP
#define MESSAGE_HPP

void msgHelp();
void showSql();
void showXss();

namespace Message {
	namespace Public {
		void MenuSql();
	}

	namespace Error {
		void ErrorInput();
	}
}

#endif
