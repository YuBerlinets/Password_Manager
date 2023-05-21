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

    void updatePassword();

    void saveNewPassword();

    void searchPassword();

    void exit();

    void changingMainPassword();

    static std::string generatingPassword();
    void saveToFile(const std::string& category,const std::string& website,const std::string& login,
                    const std::string &pass);

    unsigned int simpleHash(const std::string &pass);

    bool validatePassword(const std::string &password, const std::string &storedHash);

public:
    Menu() {
        int input;
        menuItems[0] = [this] { exit(); };
        menuItems[1] = [this] { saveNewPassword(); };
        menuItems[2] = [this] { updatePassword(); };
        menuItems[3] = [this] { searchPassword(); };
        menuItems[4] = [this] { changingMainPassword(); };
        printConsoleIntro();
        login();
        while (isRunning) {
            std::cin >> input;
            if (input < 5 && input > -1) {
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
