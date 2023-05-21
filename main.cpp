#include <iostream>
#include <algorithm>
#include <string>
#include "Menu.h"

auto main() -> int {
//    new Menu;
    std::string path = "passwords.txt";
    Manager manager(path);
    auto data = manager.loadDataFromFile();
}