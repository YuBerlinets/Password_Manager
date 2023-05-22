#include "Menu.h"

void Menu::exit() {
    Menu::isRunning = false;
}

void Menu::printMenuOptions() {
    std::cout << "1 - Save a new password" << std::endl;
    std::cout << "2 - Update a password" << std::endl;
    std::cout << "3 - Search for a password" << std::endl;
    std::cout << "4 - Changing your main password" << std::endl;
    std::cout << "5 - test loading file" << std::endl;
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

    if (validateMainPassword(pass, hash)) {
        isRunning = true;
        std::cout << std::endl;
    } else {
        std::cout << "\nIncorrect password" << std::endl;
        exit();
    }


    std::cout << std::endl;
}


bool Menu::validateMainPassword(const std::string &password, const std::string &storedHash) {
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
