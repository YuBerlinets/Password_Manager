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
    std::string password;
    bool passCorrect = false;

    static void printConsoleIntro();

    void login();

    static void printMenuOptions();

    void changingMainPassword();

    unsigned int mainPasswordHash(const std::string &password);

    bool validateMainPassword(const std::string &password, const std::string &storedHash);

    bool checkingFileExistence(const std::string &path);

    void exit();

    void saveTimeLogin(const char &log);

public:
    Menu() {

        printConsoleIntro();
        login();


        Manager manager;
        if (passCorrect) {
            std::string path;
            do {
                std::cout << "Enter the filename of path to the file: ";
                std::cin >> path;
            } while (!checkingFileExistence(path));
            Encryptor encryptor;
            encryptor.decryptFile(path, password);
            manager.loadDataFromFile();
            printMenuOptions();
            menuItems[0] = [this] { exit(); };
            menuItems[1] = [&manager] { manager.searchPassword(); };
            menuItems[2] = [&manager] { manager.sortPassword(); };
            menuItems[3] = [&manager] { manager.saveNewPassword(); };
            menuItems[4] = [&manager] { manager.updatePassword(); };
            menuItems[5] = [&manager] { manager.deletePassword(); };
            menuItems[6] = [&manager] { manager.addCategory(); };
            menuItems[7] = [&manager] { manager.removeCategory(); };
            menuItems[8] = [this] { changingMainPassword(); }; //? to keep it
            menuItems[9] = [&manager] { manager.testPrintingMap(); };
            int input;
            while (isRunning) {
                std::cin >> input;
                if (input == 0) {
                    manager.writingToFile();
                    encryptor.encryptFile(password);
                    exit();
                } else if (input > 0 && input < menuItems.size() + 1) {
                    auto f = menuItems[input];
                    f();
                    std::cout << std::endl;
                    printMenuOptions();
                } else {
                    std::cout << "Incorrect input" << std::endl;
                    printMenuOptions();
                }
            }

        }
    }

};


#endif //CPP_PROJECT_MENU_H
