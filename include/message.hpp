#ifndef MESSAGE_HPP
#define MESSAGE_HPP

void msgHelp();
void showSql();
void showXss();

namespace Message {
	namespace Default {
		void msgHelp();
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

	namespace Exit {
		void ExitMSG();
	}

	namespace App {
		void EndScan();
	}
}

#endif
