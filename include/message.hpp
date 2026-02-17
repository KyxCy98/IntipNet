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

	namespace Xss {
		void Xss();
		void Menu();
		void Warn();
	}

	namespace Error {
		void ErrorInput();
		void ErrorConnection();
		void Global();
	}

	namespace Updater {
		void UpdateML();
		void UpdateSC();
	}
}

#endif
