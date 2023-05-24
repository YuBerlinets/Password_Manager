#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <map>
#include <conio.h>
#include <windows.h>
#include <functional>
#include "Manager.h"

#ifndef CPP_PROJECT_MENU_H
#define CPP_PROJECT_MENU_H

class Menu {
private:
    bool isRunning;
    std::map<int, std::function<void()>> menuItems;

    static void printConsoleIntro();

    void login();

    static void printMenuOptions();

    void changingMainPassword();

    unsigned int mainPasswordHash(const std::string &password);

    bool validateMainPassword(const std::string &password, const std::string &storedHash);

    void exit();

public:
    Menu() {
        printConsoleIntro();
        login();
        std::string path;
        std::cout << "Enter the filename of path to the file: ";
        std::cin >> path;
        Manager manager(path);
        //test loading json file
        manager.loadDataFromFile();
        printMenuOptions();
        int input;
        menuItems[0] = [this] { exit(); };
        menuItems[1] = [&manager] { manager.saveNewPassword(); };
        menuItems[2] = [&manager] { manager.updatePassword(); };
        menuItems[3] = [&manager] { manager.searchPassword(); };
        menuItems[4] = [this] { changingMainPassword(); }; //? to keep it
        menuItems[5] = [&manager] { manager.deletePassword(); };
        menuItems[6] = [&manager] { manager.testPrintingMap(); };
        while (isRunning) {
            std::cin >> input;
            if (input > -1 && input < menuItems.size() + 1) {
                auto f = menuItems[input];
                f();
                std::cout << std::endl;
            } else
                std::cout << "Incorrect input" << std::endl;
            printMenuOptions();
        }
    }

};


#endif //CPP_PROJECT_MENU_H
