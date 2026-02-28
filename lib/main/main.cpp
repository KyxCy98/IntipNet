#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <memory>
#include "nlohmann/json.hpp"
#include "logger.hpp"
#include "message.hpp"
#include "banner.hpp"
#include "engine.hpp"
#include "AutoRun.hpp"
#include "Depencies.hpp"
#include "Secure.hpp"

using json = nlohmann::json;

void checkconnection() {
    int check = std::system("ping -c 4 google.com > /dev/null 2>&1");
    if (check == 0) {
        std::cout << "stable connection!" << std::endl;
    } else {
        Message::Error::ErrorConnection();
    }
}

class Output {
public:
    void warn(const std::string& text) {
        std::cout << "[\e[31mWRN\e[37m] " << text << std::endl;
    }
    void info(const std::string& text) {
        std::cout << "[\e[32mINF\e[37m] " << text << std::endl;
    }
    void debug(const std::string& text) {
        std::cout << "[\e[34mDBG\e[37m] " << text << std::endl;
    }
};

class Start {
private:
    std::string name, desc, shell, author, arg;
        
public:
    std::unique_ptr<Logger> log;
    Output opt;

    Start(const std::string& logPath) {
        log = std::make_unique<Logger>(logPath);
    }

    void scan(const std::string& shellcmd) {
        std::string cmd = shellcmd + " > /dev/null 2>&1";
        std::system(cmd.c_str());
        if(log) {
            log->debug(shellcmd);
            log->info("successfully executed shell");
        }
    }

    void render(const std::string& ren) {
        std::ifstream f(ren);
        if (!f.is_open()) {
            if(log) log->warn("file template not found!");
            return;
        }

        try {
            json cfg = json::parse(f);
            name   = cfg.value("name", "null");
            desc   = cfg.value("desc", "null");
            shell  = cfg.value("shell", "null");
            author = cfg.value("author", "null");
            arg    = cfg.value("arg", "null");
        } catch (const json::exception& e) {
            if(log) log->warn("HIT -> " + std::string(e.what()));
        }
    }       
};

int main() {
    auto log = std::make_unique<Logger>("debug/debug.log");
    auto shell = std::make_unique<Start>("debug/debug.log");
    
    std::string userInput;
    log->info("Started IntipNet");
    shell->scan("nmap");

    // UX: Clear Screen
    std::cout << "\033[2J\033[1;1H"; 
    log->debug("Terminal cleared successfully.");

    checkconnection();
    banner();
    log->debug("'banner()' called successfully");

    __MODULE__::__CHECK__::check_requirement();
    
    while (true) {
        std::cout << "[\033[31mroot\033[37m@intip]~# ";
        
        if (!std::getline(std::cin, userInput) || userInput == "exit" || userInput == "q") {
            log->info("User exited the session.");
            Message::Exit::ExitMSG();
            break;
        }

        secureInput(userInput);

        if (userInput == "help" || userInput == "ls") {
            log->debug("Executing help command");
            Message::Default::msgHelp();
        } 
        else if (userInput == "port") {
            log->info("Started scanning port using nmap.");
            std::string target;
            std::cout << "[\033[31mroot\033[37m@intip]~/target# ";
            std::getline(std::cin, target);

            auto scanner = std::make_unique<Auto::Exec::PortScanner>();
            scanner->start(target);
            log->debug("PortScanner started");
            scanner->end();
        }
        else if (userInput == "subdo") {
            log->info("Started scanning subdomain enumeration");
            std::string target;
            std::cout << "[\033[31mroot\033[37m@intip]~/target# ";
            std::getline(std::cin, target);

            auto scanner = std::make_unique<Auto::Exec::SubdomainEnum>();
            scanner->start(target);
            scanner->end();
        }
        else if (userInput == "archive") {
            log->info("Started scanning archive website");
            std::string target;
            std::cout << "[\033[31mroot\033[37m@intip]~/target# ";
            std::getline(std::cin, target);

            auto scanner = std::make_unique<Auto::Exec::Archive>();
            scanner->start(target);
            scanner->end();
        }
        else if (userInput == "dns") {
            log->info("Started scanning dns");
            std::string target;
            std::cout << "[\033[31mroot\033[37m@intip]~/target# ";
            std::getline(std::cin, target);

            auto scanner = std::make_unique<Auto::Exec::Dns>();
            scanner->start(target);
            scanner->end();
        }
        else if (userInput == "who") {
            log->info("Started scanning whois scan");
            std::string target;
            std::cout << "[\033[31mroot\033[37m@intip]~/target# ";
            std::getline(std::cin, target);
            
            auto scanner = std::make_unique<Auto::Exec::Whois>();
            scanner->start(target);
            scanner->end();
        }
        else if (userInput == "update") {
            log->info("User update tool");
            Auto::Exec::Update::update();
        }
        else if (userInput == "clear") {
            Engine::Command::exec("clear");
            banner();
        } 
        else if (!userInput.empty()) {
            Message::Error::ErrorInput();
            log->debug("Unknown input: " + userInput);
        }
    }

    return 0;
}