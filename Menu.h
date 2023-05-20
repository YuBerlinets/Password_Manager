#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <map>

#ifndef CPP_PROJECT_MENU_H
#define CPP_PROJECT_MENU_H


class Menu {
private:
    bool isRunning;
    std::string path = "passwords.txt";
    std::fstream inputStream;
    std::map<int, std::function<void()>> menuItems;

    static void printConsoleIntro();

    static void printMenuOptions();

    void updatePassword();

    void saveNewPassword();

    void searchPassword();

    void exit();

public:
    static void test1();

    static void test2();

    Menu() {
        isRunning = true;
        int input;
        menuItems[0] = [this] { exit(); };
        menuItems[1] = [this] { saveNewPassword(); };
        menuItems[2] = [this] { updatePassword(); };
        menuItems[3] = [this] { searchPassword(); };

        printConsoleIntro();
        printMenuOptions();

        while (isRunning) {
            std::cin >> input;
            if (input < 5 && input > -1) {
                auto f = menuItems[input];
                f();
            } else
                std::cout << "Incorrect input" << std::endl;
//            printMenuOptions();
        }
        std::cin >> input;
        std::cout << input;

    }

};

void Menu::searchPassword() {
    std::cout << "Searching for a password" << std::endl;
}

void Menu::saveNewPassword() {
    std::cout << "Saving a new password" << std::endl;
}

void Menu::updatePassword() {
    std::cout << "Updating password" << std::endl;
}

void Menu::exit() {
    Menu::isRunning = false;
}

void Menu::printMenuOptions() {
    std::cout << "1 - Save a new password" << std::endl;
    std::cout << "2 - Update a password" << std::endl;
    std::cout << "3 - Search for a password" << std::endl;
    std::cout << "0 - Exit the program" << std::endl;
}


void Menu::printConsoleIntro() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    std::string intro = "\n"
                        " /$$$$$$$                                                                    /$$       /$$      /$$                                                            \n"
                        "| $$__  $$                                                                  | $$      | $$$    /$$$                                                            \n"
                        "| $$  \\ $$/$$$$$$   /$$$$$$$ /$$$$$$$ /$$  /$$  /$$  /$$$$$$   /$$$$$$  /$$$$$$$      | $$$$  /$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ \n"
                        "| $$$$$$$/____  $$ /$$_____//$$_____/| $$ | $$ | $$ /$$__  $$ /$$__  $$/$$__  $$      | $$ $$/$$ $$ |____  $$| $$__  $$ |____  $$ /$$__  $$ /$$__  $$ /$$__  $$\n"
                        "| $$____/ /$$$$$$$|  $$$$$$|  $$$$$$ | $$ | $$ | $$| $$  \\ $$| $$  \\__/ $$  | $$      | $$  $$$| $$  /$$$$$$$| $$  \\ $$  /$$$$$$$| $$  \\ $$| $$$$$$$$| $$  \\__/\n"
                        "| $$     /$$__  $$ \\____  $$\\____  $$| $$ | $$ | $$| $$  | $$| $$     | $$  | $$      | $$\\  $ | $$ /$$__  $$| $$  | $$ /$$__  $$| $$  | $$| $$_____/| $$      \n"
                        "| $$    |  $$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$/$$$$/|  $$$$$$/| $$     |  $$$$$$$      | $$ \\/  | $$|  $$$$$$$| $$  | $$|  $$$$$$$|  $$$$$$$|  $$$$$$$| $$      \n"
                        "|__/     \\_______/|_______/|_______/  \\_____/\\___/  \\______/ |__/      \\_______/      |__/     |__/ \\_______/|__/  |__/ \\_______/ \\____  $$ \\_______/|__/      \n"
                        "                                                                                                                                  /$$  \\ $$                    \n"
                        "                                                                                                                                 |  $$$$$$/                    \n"
                        "                                                                                                                                  \\______/                     \n";
    std::cout << intro << std::endl;
    SetConsoleTextAttribute(h, 7);
}

#endif //CPP_PROJECT_MENU_H
