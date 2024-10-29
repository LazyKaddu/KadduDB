#include <iostream>
#include <string>
#include "dbms.h"

int main() {
    DBMS dbms;
    std::string input;
    
    std::cout << "Simple DBMS - Type 'exit' to quit" << std::endl;
    std::cout << "=================================" << std::endl;

    while (true) {
        std::cout << (dbms.isDatabaseSelected() ? 
                     dbms.getCurrentDatabase() : "no database") << "> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            break;
        }

        if (!input.empty()) {
            dbms.executeQuery(input);
        }
    }

    std::cout << "\nGoodbye!" << std::endl;
    return 0;
}
