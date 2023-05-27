//
// Created by ASUS on 27/05/2023.
//

#include "Encryptor.h"

void Encryptor::en_decodeFile(const std::string &file, const std::string &key) {
    std::ifstream inFile(file, std::ios::binary);
    std::ofstream outFile("tmp.json", std::ios::binary);
    std::size_t keyIndex = 0;
    char inputByte;
    while (inFile.get(inputByte)) {
        char encryptedByte = inputByte ^ key[keyIndex];
        outFile.put(encryptedByte);
    }
    inFile.close();
    outFile.close();

    std::cout << "File encrypted or decrypted successfully." << std::endl;
}