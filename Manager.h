#include <map>
#include <string>
#include <vector>
#ifndef CPP_PROJECT_MANAGER_H
#define CPP_PROJECT_MANAGER_H


class Manager {
private:
    const std::string filePath;
    //<category, all other fields>
    std::map<std::string, std::vector<std::string>> data;
//    void updatePassword();
//
//    void saveNewPassword();
//
//    void searchPassword();
//    static std::string generatingPassword();
//    void saveToFile(const std::string& category,const std::string& website,const std::string& login,
//                    const std::string &pass);
public:
    Manager(std::string &path) : filePath(path) {

    }

    const std::string &getFilePath() const {
        return filePath;
    }

    std::map<std::string, std::vector<std::string>> loadDataFromFile();

};


#endif //CPP_PROJECT_MANAGER_H
