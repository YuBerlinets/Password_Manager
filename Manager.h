#include <map>
#include <string>
#include <vector>
#include "Encryptor.h"

#ifndef CPP_PROJECT_MANAGER_H
#define CPP_PROJECT_MANAGER_H


/**
 * @brief Manager provides all necessary functionality on passwords.
 * such as sorting, searching etc.
 *
 */
class Manager {
private:
    const std::string filePath;
    //<category(map) -> website(map) -> login and pass (vector)>
    //<category, <website, <login, password>>>
    std::map<std::string, std::map<std::string, std::vector<std::string>>> data;
    /**
     * \brief Password generation.
     *
     * Generates a password depending on user input, such that
     * - number of characters
     * - lower, upper or both cases
     * - including special symbols or no
     * @return generated password
     */
    static std::string generatingPassword();
    /**
     * \brief Saving data to vector.
     *
     * store data from entire map "data" data to vector in order to sort it
     * in the future
     * @return vector with all categories, websites, logins and passwords
     */
    std::vector<std::vector<std::string>> savingPasswordsForSorting();

    /**
     * \brief Printing sorted data.
     *
     * Prints alphabetically sorted data from given vector, depending on user's input
     * c - only category
     * w - only website
     * b - both
     * @param vector not sorted vector with all data
     */
    static void printDataForSorting(const std::vector<std::vector<std::string>> &vector);

    Encryptor encryptor;

public:
    Manager() {

    }

    /**
     * \brief Sorting data
     *
     * Prints sorted information, depending on user's input\n
     * c - only category\n
     * w - only website\n
     * b - both
     */
    void sortPassword();
    /**
     * \brief Searching for exact password.
     *
     * Prints a information about password, which user were looking for.\n
     * User's input:\n
     * 1. category\n
     * 2. website
     */
    void searchPassword();
    /**
     * \brief Saving new password
     *
     * Saves a new password to the map "data".\n
     * Asks all necessary information from user - category, website, login and
     * generating password.\n
     * Generating based on user's input might be generating automatically
     * according to "generatingPassword" method, otherwise user should write password
     * by themself.
     * @see generatingPassword()
     */
    void saveNewPassword();
    /**
     * \brief Updating password for website.
     *
     *  Updates already existed record.\n
     *  Takes from user category and website, checks if such website exists in our "data".\n
     *  If website exists, it will ask user to enter new password.
     */
    void updatePassword();
    /**
     * \brief Deleting existed password.
     *
     * Deletes already existed password.\n
     * Takes from user website, checks if such website exists in our "data".\n
     * If website exists, it will delete all information about that website.
     */
    void deletePassword();
    /**
     * \brief Adding new category.
     *
     * Adds new empty category to our map "data".\n
     * Asks user to enter a new name for category.\n
     * Checks if category with entered name doesn't exist, if not creates new.
     */
    void addCategory();

    /**
     * \brief Removing existed category.
     *
     * Deletes entire category.\n
     * Asks user to enter a new name for category.\n
     * Checks if category with entered name exists, then delete all data connected to it
     */
    void removeCategory();

    /**
     * \brief Loading data from file to map.
     *
     * Reads all data from decrypted json file, using nlohmann library and
     * saves it to map "data", which represents such structure:\n
     * std::map<std::string, std::map<std::string, std::vector<std::string>>> data\n
     * <category, <website, <login, password>>>\n
     * - map with "Category" as key, and map "CategoryValue" as value\n
     * - map with "Website" as key and vector of string as value\n
     * - vector where only two elements: login and password.
     */
    void loadDataFromFile();
    /**
     * \brief Saving data to file.
     *
     * Writes all data from our map "data" to json file, using nlohmann library.\n
     * After writing to the file it will be immediately encrypted using XOR cypher.
     */
    void writingToFile();

};


#endif //CPP_PROJECT_MANAGER_H
