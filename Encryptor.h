#ifndef CPP_PROJECT_ENCRYPTOR_H
#define CPP_PROJECT_ENCRYPTOR_H

#include <string>
#include <fstream>
#include <iostream>

class Encryptor {
private:
    std::string path;
public:
    void en_decodeFile(const std::string &file, const std::string &key);
};


#endif //CPP_PROJECT_ENCRYPTOR_H
