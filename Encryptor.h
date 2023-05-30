#ifndef CPP_PROJECT_ENCRYPTOR_H
#define CPP_PROJECT_ENCRYPTOR_H

#include <string>
#include <fstream>
#include <iostream>

class Encryptor {
private:
    std::string path;
public:
    /**
     * \brief Decrypting data in file.
     *
     * Decrypts the file passed as 1st parameter(it's that file,
     * that we enter when we start our program), using first letter of our password
     * passed as second argument.\n
     * Method uses standard XOR cypher, which
     * implement XOR operator on every char from the first file,
     * passed as first argument and put it on the tmp json file from which we will
     * read all the data to store in our map "data".
     * @param file File we entered on the start of our program.
     * @param key Our main password.
     */
    void decryptFile(const std::string &file, const std::string &key);
    /**
     * \brief Encrypting data in file.
     *
     * This method calls when we end executing of our program. \n
     * It would take all the data from tmp json file, where we store all our data
     * after all changes during our session in app and encrypt it using similar to
     * "decryptFile" XOR method.
     * @see decryptFile(const std::string &file, const std::string &key)
     * @param key Our main password.
     * @param file File that we entered on the start
     */
    void encryptFile(const std::string &file, const std::string &key);
};


#endif //CPP_PROJECT_ENCRYPTOR_H
