//
// Created by daniel on 9/7/16.
//

#include "Config.h"

std::string Config::getDataDir() {
    std::string home(getenv("HOME"));
    return home + "/ClionProjects/Coding-Problems/dataFiles/";
}
