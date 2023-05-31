#include <ctime>
#include "Menu.h"

bool Menu::checkingFileExistence(const std::string &path) {
    std::ifstream f(path.c_str());
    return f.good();
}

void Menu::exit() {

    Menu::isRunning = false;
}

void Menu::printMenuOptions() {
    std::cout << "1 - Search for a password" << std::endl;
    std::cout << "2 - Sort passwords" << std::endl;
    std::cout << "3 - Save a new password" << std::endl;
    std::cout << "4 - Update a password" << std::endl;
    std::cout << "5 - Delete a password" << std::endl;
    std::cout << "6 - Add category" << std::endl;
    std::cout << "7 - Delete category" << std::endl;
    std::cout << "8 - Changing your main password" << std::endl;
    std::cout << "0 - Exit the program" << std::endl;
    std::cout << "Enter your choice: ";
}

void Menu::changingMainPassword() {
    std::string pass;
    std::cout << "Enter your new password: ";
    std::cin >> pass;
    auto file = std::fstream("passKey.txt");
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
    auto file = std::fstream("passKey.txt");
    std::string hash;
    file >> hash;
    char ch;
    int attempts = 3;

    while (attempts != 0) {
        std::cout << "Enter the password: ";
        while ((ch = getch()) != '\r') {
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

        if (validateMainPassword(pass, hash)) {
            isRunning = true;
            password = pass;
            passCorrect = true;
            saveTimeLogin();
            std::cout << std::endl;
            break;
        } else {
            saveTimeLogin();
            pass = "";
            std::cout << "\nIncorrect password" << std::endl;
            attempts--;
            std::cout << "You have " << attempts << " attempts left" << std::endl;
        }
    }
    if (attempts == 0) {
        std::cout << "You typed incorrect password 3 times. GoodBye!" << std::endl;
        exit();
    }
}

void Menu::saveTimeLogin() {
    std::fstream file("timestamp.txt");
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);
    srand((unsigned) time(NULL));
    int random;
    random = 1000 + (std::rand() % (4000 - 1000 + 1));
    std::string space = std::to_string(random) + "\n\n\n\n\n\n\n\n\n\n";
    int year = localTime->tm_year;
    int month = localTime->tm_mon;
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    file << space << hour << space << minute << space << day << space << month + 1 << space << year + 1900 << space;
}

bool Menu::validateMainPassword(const std::string &password, const std::string &storedHash) {
    unsigned int hashedPassword = mainPasswordHash(password);
    std::string hashString = std::to_string(hashedPassword);

    return (hashString == storedHash);
}


void Menu::actionsType() {
    int input;
    bool validInput = false;
    do {

        std::cout << "Enter what type of operation you would like to do" << std::endl;
        std::cout << "1 - Provide file of path to file." << std::endl;
        std::cout << "2 - Create a new file." << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> input;
        switch (input) {
            case 1:
                do {
                    std::cout << "Enter the filename of path to the file: ";
                    std::cin >> path;
                } while (!checkingFileExistence(path));
                validInput = true;
                break;
            case 2: {
                std::string name;
                std::cout << "Enter the name of new file with file extension(.json)" << std::endl;
                std::cout << "-> ";
                std::cin >> name;
                creationNewFile(name);
                validInput = true;
                break;
            }
            default:
                std::cout << "Incorrect input" << std::endl;
        }
    } while (!validInput);
}

void Menu::creationNewFile(const std::string &name) {
    newFile = true;
    path = name;
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
