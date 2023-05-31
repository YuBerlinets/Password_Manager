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

/**
 * @brief Menu class which takes a input from user in order
 * to give access to functionality
 */
class Menu {
private:
    bool isRunning = false;
    std::map<int, std::function<void()>> menuItems;
    std::string password;
    std::string path;
    bool passCorrect = false;
    bool newFile = false;

    /**
     * Prints text "Password manager" to the console.
     */
    static void printConsoleIntro();

    /**
     * \brief Choosing the file.
     *
     * Asks user on which file them would like to perform actions.\n
     * Asks for the path to the existing file or create a new one.
     */
    void actionsType();

    void creationNewFile(const std::string &name);

    /**
     * \brief Login to an app.
     *
     * Asks user to input password and checks previously saved hash of this password
     * if password is correct then program continue its executing,
     * sets "isRunning" to true and "passCorrect" to true.\n
     * If user fails 3 attempts to enter the password, program will immediately close.
     */
    void login();

    /**
     * \brief Prints all available options to the user.
     *
     * 1 - Search for a password\n
     * 2 - Sort passwords\n
     * 3 - Save a new password\n
     * 4 - Update a password\n
     * 5 - Delete a password\n
     * 6 - Add category\n
     * 7 - Delete category\n
     * 0 - Exit the program
     */
    static void printMenuOptions();

    void changingMainPassword();

    /**
     * Generates hash from the given password.
     * @param password - given password.
     * @return hash as unsigned int.
     */
    unsigned int mainPasswordHash(const std::string &password);

    /**
     * \brief Password validation
     *
     * Validate if the password entered by user is similar to already stored in system.
     * @param password - Password entered by user.
     * @param storedHash - Stored hash of main password.
     * @return True or false, depending on correctness of entered password.
     */
    bool validateMainPassword(const std::string &password, const std::string &storedHash);

    /**
     * \brief Checks if the file entered by user exists.
     *
     * @param path - Path to the file.
     * @return True, if file exists and false if it doesn't.
     */
    static bool checkingFileExistence(const std::string &path);

    /**
     * \brief Finishes executing of the program.
     *
     * Sets isRunning field to false.
     */
    void exit();

    /**
     * \brief Saving time of login.
     *
     * Saves login time to the file, using separation to make it more secure.
     */
    void saveTimeLogin();

public:
    Menu() {
        printConsoleIntro();
        login();
        actionsType();


        Manager manager;
        if (passCorrect) {
            Encryptor encryptor;
            if (!newFile) {
                encryptor.decryptFile(path, password);
                manager.loadDataFromFile();
            }
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
            int input;
            while (isRunning) {
                std::cin >> input;
                if (input == 0) {
                    manager.writingToFile();
                    encryptor.encryptFile(path,password);
                    exit();
                } else if (input > 0 && input < menuItems.size()) {
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
