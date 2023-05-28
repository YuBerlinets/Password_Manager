#include <map>
#include <string>
#include <vector>
#include "Encryptor.h"

#ifndef CPP_PROJECT_MANAGER_H
#define CPP_PROJECT_MANAGER_H


class Manager {
private:
    const std::string filePath;
    //<category(map) -> website(map) -> login and pass (vector)>
    //<category, <website, <login, password>>>
    std::map<std::string, std::map<std::string, std::vector<std::string>>> data;

    static std::string generatingPassword();


    std::vector<std::vector<std::string>> savingPasswordsForSorting();

    static void printDataForSorting(const std::vector<std::vector<std::string>> &vector);

    Encryptor encryptor;

public:
    Manager() {

    }


    void sortPassword();

    void searchPassword();

    void saveNewPassword();

    void updatePassword();

    void deletePassword();

    void addCategory();

    void removeCategory();

    void loadDataFromFile();

    void writingToFile();

    //test
    void testPrintingMap();
};


#endif //CPP_PROJECT_MANAGER_H
