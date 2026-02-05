#ifndef MESSAGE_HPP
#define MESSAGE_HPP

void msgHelp();
void showSql();
void showXss();

namespace Message {
	namespace Default {
		void msgHelp();
		void showSql();
	}
	
	namespace Sql {
		void Sql();
		void Menu();
		void Error();
		void dumpSql();
	}

	namespace Error {
		void ErrorInput();
		void ErrorConnection();
	}

	namespace Updater {
		void UpdateML();
		void UpdateSC();
	}
}

#endif
