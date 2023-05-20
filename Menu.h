#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

#ifndef CPP_PROJECT_MENU_H
#define CPP_PROJECT_MENU_H


class Menu {
private:
    bool isRunning;
    std::string path = "passwords.txt";
    std::fstream inputStream;

    void printConsoleIntro();

public:
    Menu() {
        isRunning = false;
        std::string input;
        printConsoleIntro();
        while (isRunning) {
            std::getline(std::cin, input);
            std::cout << input << std::endl;
        }
    }

};

void Menu::printConsoleIntro() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    std::cout
            <<"######\n"
              "#     #   ##    ####   ####  #    #  ####  #####  #####     #    #   ##   #    #   ##    ####  ###### #####\n"
              "#     #  #  #  #      #      #    # #    # #    # #    #    ##  ##  #  #  ##   #  #  #  #    # #      #    #\n"
              "######  #    #  ####   ####  #    # #    # #    # #    #    # ## # #    # # #  # #    # #      #####  #    #\n"
              "#       ######      #      # # ## # #    # #####  #    #    #    # ###### #  # # ###### #  ### #      #####\n"
              "#       #    # #    # #    # ##  ## #    # #   #  #    #    #    # #    # #   ## #    # #    # #      #   #\n"
              "#       #    #  ####   ####  #    #  ####  #    # #####     #    # #    # #    # #    #  ####  ###### #    # \n";
    SetConsoleTextAttribute(h, 15);
}

#endif //CPP_PROJECT_MENU_H
