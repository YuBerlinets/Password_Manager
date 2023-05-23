#include <map>
#include <string>
#include <vector>

#ifndef CPP_PROJECT_MANAGER_H
#define CPP_PROJECT_MANAGER_H


class Manager {
private:
    const std::string filePath;
    //<category(map) -> website(map) -> login and pass (vector)>
    std::map<std::string, std::map<std::string, std::vector<std::string>>> data;

    static std::string generatingPassword();

    void writingToFile(std::string &newData);

    void addDataToMap(const std::string &category, const std::vector<std::string> &info);

public:
    Manager(std::string &path) : filePath(path) {

    }

    void saveNewPassword();

    const std::string &getFilePath() const {
        return filePath;
    }

    void updatePassword();

    void deletePassword();
    //test
    void testPrintingMap();

    void searchPassword();

    void loadDataFromFile();

};


#endif //CPP_PROJECT_MANAGER_H
