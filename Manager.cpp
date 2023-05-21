#include <iostream>
#include "Manager.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>

std::map<std::string, std::vector<std::string>> Manager::loadDataFromFile() {
    std::ifstream file(getFilePath());
    std::string line;
    std::map<std::string, std::vector<std::string>> data;
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
    for (const auto &pair: data) {
        std::cout << "Key: " << pair.first << std::endl;
        std::cout << "Values: ";
        const std::vector<std::string> &values = pair.second;
        for (const std::string &value: values) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    return data;
}
