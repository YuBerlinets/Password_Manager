#include "Menu.h"

/**
 * @mainpage Password Manager
 * @section intro_sec Main Goal
 * Password manager is used for storing and managing your passwords.\n
 * All files which store information about our passwords are encrypted.\n
 * While executing  our program user are given that functionality:\n
 * - Search passwords - returns passwords that contain specific parameters.\n
 * - Sort passwords - returns a sorted list of all passwords.
 * It should allow sorting by at least 2 different parameters at the same time, such as by name and category.\n
 * - Add password - adds a new password to the encrypted file.
 * The user should be given the option to enter their own password and
 * informed about how secure the password is and whether it has been used before.
 * Additionally, an automatically generated password should be proposed to the user,
 * giving them the option to choose certain parameters such as:\n
 *
 * Number of characters;\n
 * Whether to include uppercase and lowercase letters;\n
 * Whether to include special characters.\n
 *
 * - Edit password - allows editing of data in an existing password.\n
 * - Delete password(s) - deletes the selected password or passwords. Before each deletion,
 * we should notify the user, especially if more than one password is being deleted.\n
 * - Add category - adds a new category that we can use when creating new passwords.\n
 * - Delete category - deletes the category along with all the passwords assigned to that category.\n
 */
auto main() -> int {
    new Menu;
}

//TODO change main menu 3 points