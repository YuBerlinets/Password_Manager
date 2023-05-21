#include "Menu.h"

unsigned int Menu::mainPasswordHash(const std::string &password) {

    std::string defaultPassword = password;
    unsigned int hash = 0;
    for (char c: defaultPassword) {
        hash += static_cast<unsigned int>(c);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void Menu::searchPassword() {
    std::cout << "Searching for a password" << std::endl;
}

void Menu::saveNewPassword() {
    std::string website;
    std::string login;
    std::string pass;
    std::string result;
    char ownPass;
    std::cout << "Saving a new password" << std::endl;
    std::cout << "Enter the website what the password for: ";
    std::cin >> website;
    std::cout << "Enter the login: ";
    std::cin >> login;
    std::cout << "Do you want to generate automatically password(y/n)? ";
    std::cin >> ownPass;
    if (ownPass == 'y') {
        pass = generatingPassword();
        std::cout << "Password -> " + pass << std::endl;
    } else {
        std::cout << "Enter the password: ";
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!pass.empty()) {
                    pass.pop_back();
                    std::cout << "\b \b";
                }
            } else {
                pass.push_back(ch);
                std::cout << '*';
            }
        }
    }
    std::cout << std::endl;
    result = website + ":" + login + ":" + pass;
//    int resultHash = simpleHash(result);

    std::cout << result << std::endl;
}

const std::string specSymb = "!@#$%^&*";
const std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
const std::string numbers = "0123456789";

std::string Menu::generatingPassword() {
    int length;
    char parameter1;
    char parameter2;
    std::string sample = numbers;
    std::string result;
    std::cout << "Enter the length of password: ";
    std::cin >> length;
    std::cout << "Enter the parameter of password:"
                 "\nl - only lower case"
                 "\nu - only upper case"
                 "\nb - both lower and upper case"
                 "\n -> ";
    std::cin >> parameter1;
    std::cout << "Should it contains a special characters(y/n): ";
    std::cin >> parameter2;
    parameter2 == 'y' ? sample += specSymb : sample = sample;
    if (parameter1 == 'l') {
        sample += lowerCase; //? only lower but the numbers also ?
    } else if (parameter1 == 'u') {
        sample += upperCase;
    } else {
        sample += upperCase + lowerCase;
    }
    std::random_shuffle(sample.begin(), sample.end());

    for (int i = 0; i < length; ++i) {
        int randomChar = rand() % sample.length();
        result.push_back(sample.at(randomChar));
    }


    return result;
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
    std::cout << "4 - Changing your main password" << std::endl;
    std::cout << "0 - Exit the program" << std::endl;
    std::cout << "Enter your choice: ";
}

void Menu::changingMainPassword() {
    std::string pass;
    std::cout << "Enter your new password: ";
    std::cin >> pass;
    auto file = std::fstream("test.txt");
    int hashedPass = mainPasswordHash(pass);
    file << hashedPass;
    std::cout << "Your new password has been successfully stored" << std::endl;
}

void Menu::login() {
    std::string pass;
    std::cout << "Enter the password: ";
    char ch;

    DWORD consoleMode;
    HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(inputHandle, &consoleMode);
    SetConsoleMode(inputHandle, consoleMode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                std::cout << "\b \b";
            }
        } else {
            pass.push_back(ch);
            std::cout << '*';
        }
    }

    auto file = std::fstream("test.txt");
    std::string hash;
    file >> hash;

    SetConsoleMode(inputHandle, consoleMode);

    if (validatePassword(pass, hash)) {
        isRunning = true;
        std::cout << std::endl;
        printMenuOptions();
    } else {
        std::cout << "\nIncorrect password" << std::endl;
        exit();
    }


    std::cout << std::endl;
}


bool Menu::validatePassword(const std::string &password, const std::string &storedHash) {
    unsigned int hashedPassword = mainPasswordHash(password);
    std::string hashString = std::to_string(hashedPassword);

    return (hashString == storedHash);
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
