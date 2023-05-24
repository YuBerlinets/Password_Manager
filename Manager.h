#include <map>
#include <string>
#include <vector>

#ifndef CPP_PROJECT_MANAGER_H
#define CPP_PROJECT_MANAGER_H


class Manager {
private:
    const std::string filePath;
    //<category(map) -> website(map) -> login and pass (vector)>
    //<category, <website, <login, password>>>
    std::map<std::string, std::map<std::string, std::vector<std::string>>> data;

    static std::string generatingPassword();

    void writingToFile(std::string &newData);

public:
    Manager(std::string &path) : filePath(path) {

    }


    const std::string &getFilePath() const {
        return filePath;
    }

    void sortPassword();

    void searchPassword();

    void saveNewPassword();

    void updatePassword();

    void deletePassword();

    void addCategory();

    void removeCategory();

    void loadDataFromFile();

    //test
    void testPrintingMap();
};


#endif //CPP_PROJECT_MANAGER_H
