#include <iostream>
#include "Manager.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <conio.h>


void Manager::writingToFile(std::string &newData) {
    auto file = std::ofstream(getFilePath());
    file << newData;
}

void Manager::loadDataFromFile() {
    std::ifstream file(getFilePath());
    std::string line;
//    std::map<std::string, std::vector<std::string>> data;
    while (std::getline(file, line)) {
        std::size_t delimiterPos = line.find('-');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string valuesStr = line.substr(delimiterPos + 1);

            std::vector<std::string> values;
            std::size_t colonPos = valuesStr.find(':');
            while (colonPos != std::string::npos) {
                std::string value = valuesStr.substr(0, colonPos);
                values.push_back(value);
                valuesStr = valuesStr.substr(colonPos + 1);
                colonPos = valuesStr.find(':');
            }
            values.push_back(valuesStr);

            data[key] = values;
        }
    }
    //printing data only for tests
    for (const auto &keys: data) {
        std::cout << "Key: " << keys.first << std::endl;
        std::cout << "Values: ";
        const std::vector<std::string> &values = keys.second;
        for (const std::string &value: values) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

void Manager::searchPassword() {
    std::cout << "Searching for a password" << std::endl;
    std::cout << "Enter category: ";
    std::string category;
    std::cin >> category;
    std::vector<std::string> info = data.at(category);
    for (auto &value: info)
        std::cout << value + " ";
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
    std::cout << "Updating password" << std::endl;
}

void Manager::saveNewPassword() {
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
    writingToFile(result);
    std::cout << result << std::endl;
}
