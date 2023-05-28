#include "Encryptor.h"
#include <filesystem>

void Encryptor::decryptFile(const std::string &file, const std::string &key) {
    std::ifstream inFile(file, std::ios::binary);
    std::ofstream outFile("tmp.json", std::ios::binary);
    std::size_t keyIndex = 0;
    char inputByte;
    while (inFile.get(inputByte)) {
        char encryptedByte = inputByte ^ key[keyIndex];
        outFile.put(encryptedByte);
    }
    inFile.close();

    std::cout << "File decrypted successfully." << std::endl;
}

void Encryptor::encryptFile(const std::string &key) {
    std::ifstream inFile("writingTMP.json", std::ios::binary);
    std::ofstream outFile("passwords.json", std::ios::binary);
    std::size_t keyIndex = 0;
    char inputByte;
    while (inFile.get(inputByte)) {
        char encryptedByte = inputByte ^ key[keyIndex];
        outFile.put(encryptedByte);
    }
    inFile.close();

    std::filesystem::remove("writingTMP.json");
    std::cout << "File encrypted successfully." << std::endl;
}