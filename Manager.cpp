#include <iostream>
#include "Manager.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <conio.h>
#include <json.hpp>
#include <filesystem>
#include <algorithm>

using json = nlohmann::json;


//TODO dopylyt` writingToFile method
void Manager::writingToFile() {
    json jsonData;
    for (const auto &category: data) {
        const std::string &categoryName = category.first;
        const std::map<std::string, std::vector<std::string>> &categoryData = category.second;

        json websitesJsonArray;

        for (const auto &website: categoryData) {
            const std::string &websiteName = website.first;
            const std::vector<std::string> &websiteValues = website.second;
            json websiteJsonObject;
            websiteJsonObject["website"] = websiteName;
            websiteJsonObject["login"] = websiteValues[0];
            websiteJsonObject["password"] = websiteValues[1];

            websitesJsonArray.push_back(websiteJsonObject);
        }


        jsonData[categoryName] = websitesJsonArray;
    }

    std::ofstream file("writingTMP.json");

    file << jsonData.dump(3);
    file.close();

}


void Manager::loadDataFromFile() {
    std::ifstream file("tmp.json");
    json jsonData;
    file >> jsonData;

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
    file.close();
    std::filesystem::remove("tmp.json");
}

void Manager::sortPassword() {
    char type;
    std::vector<std::vector<std::string>> sortedPasswords = savingPasswordsForSorting();
    std::cout << "Enter type of sort"
                 "\nc - only category"
                 "\nw - only website"
                 "\nb - both category and website"
                 "\n - > ";
    std::cin >> type;

    switch (type) {
        case 'c'://ask about lowercase
            std::ranges::sort(sortedPasswords.begin(), sortedPasswords.end(),
                              [](const std::vector<std::string> &a, const std::vector<std::string> &b) {
                                  std::string firstWord = a[0];
                                  std::string secondWord = b[0];
                                  std::transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::tolower);
                                  std::transform(secondWord.begin(), secondWord.end(), secondWord.begin(), ::tolower);
                                  return firstWord < secondWord;
                              });
            printDataForSorting(sortedPasswords);
            break;
        case 'w':
            std::ranges::sort(sortedPasswords.begin(), sortedPasswords.end(),
                              [](const std::vector<std::string> &a, const std::vector<std::string> &b) {
                                  std::string firstWord = a[1];
                                  std::string secondWord = b[1];
                                  std::transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::tolower);
                                  std::transform(secondWord.begin(), secondWord.end(), secondWord.begin(), ::tolower);
                                  return firstWord < secondWord;
                              });
            printDataForSorting(sortedPasswords);
            break;
        case 'b':
            std::ranges::sort(sortedPasswords.begin(), sortedPasswords.end(),
                              [](const std::vector<std::string> &a, const std::vector<std::string> &b) {
                                  std::string firstWord = a[1];
                                  std::string secondWord = b[1];
                                  std::transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::tolower);
                                  std::transform(secondWord.begin(), secondWord.end(), secondWord.begin(), ::tolower);
                                  if (a[0] != b[0])
                                      return a[0] < b[0];
                                  else
                                      return firstWord < secondWord;
                              });
            printDataForSorting(sortedPasswords);
            break;
        default:
            std::cout << "Incorrect input";
    }

}

void Manager::printDataForSorting(const std::vector<std::vector<std::string>> &vector) {
    for (auto &firstItem: vector) {
        std::cout << "=-=-=-=-=-=-=" << std::endl;
        std::cout << "Category: " + firstItem[0] << std::endl;
        std::cout << "Website: " + firstItem[1] << std::endl;
        std::cout << "Login: " + firstItem[2] << std::endl;
        std::cout << "Password: " + firstItem[3] << std::endl;
        std::cout << "=-=-=-=-=-=-=" << std::endl;

    }
}

std::vector<std::vector<std::string>> Manager::savingPasswordsForSorting() {
    std::vector<std::vector<std::string>> sortedPasswords;

    for (const auto &category: data) {
        const std::string &categoryName = category.first;
        const std::map<std::string, std::vector<std::string>> &categoryValue = category.second;

        for (const auto &website: categoryValue) {
            const std::string &websiteName = website.first;
            const std::vector<std::string> &websiteValues = website.second;

            std::vector<std::string> passwordEntry;
            passwordEntry.push_back(categoryName);
            passwordEntry.push_back(websiteName);
            passwordEntry.push_back(websiteValues[0]);
            passwordEntry.push_back(websiteValues[1]);

            sortedPasswords.push_back(passwordEntry);
        }
    }
    return sortedPasswords;
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
    }
    std::vector<std::string> resultLoginPass;
    resultLoginPass.push_back(login);
    resultLoginPass.push_back(pass);

    if (data[category].size() == 1 && data[category].count("") > 0) {
        auto tmpMap = std::move(data[category]);
        data[category][website] = resultLoginPass;
    } else {
        data[category][website] = resultLoginPass;
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
        sample += lowerCase;
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




