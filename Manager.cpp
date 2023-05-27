#include <iostream>
#include "Manager.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <conio.h>
#include <json.hpp>

using json = nlohmann::json;




//TODO dopylyt` writingToFile method
void Manager::writingToFile(std::string &newData) {
//    auto file = std::ofstream(getFilePath());
//    file << newData;
}


void Manager::loadDataFromFile() {
    std::ifstream file(getFilePath());

    json jsonData;
    file >> jsonData;
    std::string test;

    for (const auto &category: jsonData.items()) {
        std::string categoryName = category.key();
        const auto &categoryData = category.value();

        for (const auto &item: categoryData) {
            std::string website = item["website"];
            std::string login = item["login"];
            std::string password = item["password"];

            data[categoryName][website].push_back(login);
            data[categoryName][website].push_back(password);
        }
    }
}

//TODO update sortPassword method
void Manager::sortPassword() {
    char type;
    std::cout << "Enter type of sort"
                 "\nc - only category"
                 "\nw - only website"
                 "\nb - both category and website"
                 "\n - > ";
    std::cin >> type;
    switch (type) {
        case 'c':
            for (const auto &category: data) {
                const std::map<std::string, std::vector<std::string>> &categoryValue = category.second;
                for (const auto &website: categoryValue) {
                    const std::vector<std::string> &websiteValues = website.second;
                    std::cout << "=-=-=-=-=-=-=" << std::endl;
                    std::cout << "Category: " + category.first << std::endl;
                    std::cout << "Website: " + website.first << std::endl;
                    std::cout << "Login: " + websiteValues[0] << std::endl;
                    std::cout << "Password: " + websiteValues[1] << std::endl;
                    std::cout << "=-=-=-=-=-=-=" << std::endl;
                }
            }
            break;
        case 'w':
            break;
        case 'b':
            break;
        default:
            std::cout << "Incorrect input";
    }
}

void Manager::searchPassword() {
    std::cout << "Searching for a password" << std::endl;
    std::cout << "Enter category: ";
    std::string categorySearch;
    std::cin >> categorySearch;
    std::cout << "Enter the website: ";
    std::string websiteSearch;
    std::cin >> websiteSearch;
    if (data.contains(categorySearch) && data[categorySearch].contains(websiteSearch)) {
        std::string login = data[categorySearch][websiteSearch][0];
        std::string password = data[categorySearch][websiteSearch][1];
        std::cout << "=-=-=-=-=-=-=" << std::endl;
        std::cout << "Category: " + categorySearch << std::endl;
        std::cout << "Login: " + login << std::endl;
        std::cout << "Password: " + password << std::endl;
        std::cout << "=-=-=-=-=-=-=" << std::endl;
    } else
        std::cout << "Password for such parameters hasn't been found" << std::endl;

}

void Manager::saveNewPassword() {
    std::string category;
    std::string website;
    std::string login;
    std::string pass;
    char ownPass;
    std::cout << "Saving a new password" << std::endl;
    std::cout << "Enter the category: ";
    std::cin >> category;
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
    std::vector<std::string> resultLoginPass;
    resultLoginPass.push_back(login);
    resultLoginPass.push_back(pass);

    if (data[category].size() == 1) {
        auto tmpMap = data[category].extract("");
        tmpMap.key() = website;
    }

    data[category][website] = resultLoginPass;
    std::cout << std::endl;
    std::cout << "Your password for website: " + website + " was successfully saved" << std::endl;
}

const std::string specSymb = "!@#$%^&*";
const std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
const std::string numbers = "0123456789";

std::string Manager::generatingPassword() {
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

    srand((unsigned) time(NULL));
    for (int i = 0; i < length; ++i) {
        int randomChar = rand() % sample.length();
        result.push_back(sample.at(randomChar));
    }

    return result;
}


void Manager::updatePassword() {
    std::string websiteUpdate;
    std::string passUpdate;
    std::cout << "Enter the website for which you want to update the password: " << std::endl;
    std::cin >> websiteUpdate;
    std::cout << "Enter the password: ";
    char ch;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!passUpdate.empty()) {
                passUpdate.pop_back();
                std::cout << "\b \b";
            }
        } else {
            passUpdate.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    for (auto &category: data) {
        std::map<std::string, std::vector<std::string>> &categoryValue = category.second;
        if (categoryValue.count(websiteUpdate) > 0) {
            categoryValue[websiteUpdate][1] = passUpdate;
            std::cout << "Password for " << websiteUpdate << " was successfully updated" << std::endl;
            return;
        }
    }
    std::cout << "Website - " << websiteUpdate << " hasn't been found" << std::endl;
}

void Manager::deletePassword() {
    std::cout << "Enter the name of the website for deleting password: ";
    std::string websiteDelete;
    std::cin >> websiteDelete;
    for (auto &category: data) {
        std::map<std::string, std::vector<std::string>> &categoryValue = category.second;
        if (categoryValue.count(websiteDelete) > 0) {
            categoryValue.erase(websiteDelete);
            std::cout << "Password for " << websiteDelete << " was successfully deleted" << std::endl;
            return;
        }
    }
    std::cout << "Website - " << websiteDelete << " hasn't been found" << std::endl;
}


void Manager::addCategory() {
    std::string categoryInput;
    std::cout << "Enter new category: ";
    std::cin >> categoryInput;
    std::string tmp = "";
    std::vector<std::string> tmpVec = {"", ""};

    if (data.contains(categoryInput))
        std::cout << categoryInput + " are already exits" << std::endl;
    else {
        data[categoryInput][tmp] = tmpVec;
        std::cout << "New category - " + categoryInput + " was successfully created" << std::endl;
    }
}

void Manager::removeCategory() {
    std::string categoryRemove;
    std::cout << "Enter the category to remove: ";
    std::cin >> categoryRemove;
    if (data.contains(categoryRemove)) {
        data.erase(categoryRemove);
        std::cout << "Category - " + categoryRemove + " was successfully deleted" << std::endl;
    } else
        std::cout << "Category - " + categoryRemove + " hasn't been found" << std::endl;

}

void Manager::testPrintingMap() {
    for (const auto &category: data) {
        const std::map<std::string, std::vector<std::string>> &categoryValue = category.second;
        for (const auto &website: categoryValue) {
            const std::vector<std::string> &websiteValues = website.second;
            std::cout << "=-=-=-=-=-=-=" << std::endl;
            std::cout << "Category: " + category.first << std::endl;
            std::cout << "Website: " + website.first << std::endl;
            std::cout << "Login: " + websiteValues[0] << std::endl;
            std::cout << "Password: " + websiteValues[1] << std::endl;
            std::cout << "=-=-=-=-=-=-=" << std::endl;
        }
    }
}

void Manager::saveTimeLogin() {
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);
    std::fstream file("timestamp.txt");
    int year = localTime->tm_year;
    int month = localTime->tm_mon;
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
//    std::string result = "Last login at " + hour + ":" + minute + ":" + second + "-" +
//                         day + ":" + month + ":" + year;

    file << "Last login: " << hour << ":" << minute << "-" << day << "/" << month + 1 << "/" << year + 1900;


}
