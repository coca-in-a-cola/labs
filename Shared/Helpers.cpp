#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <format>
#include <stdio.h>
#include <cstdlib>
#include "Helpers.h"

namespace Helpers {

    std::filesystem::path getFullPath(std::string& filepath) {
        return std::filesystem::current_path() / filepath;
    }

    void drawFile(std::string filepath) {
        std::string content;
        auto fullPath = getFullPath(filepath);
        std::ifstream file(fullPath);

        if (!file.is_open()) {
            std::cout << std::format("file not found in filepath {}", fullPath.string()) << std::endl;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }

    void clearConsole() {
    #if defined(_WIN32) || defined(WIN32)
        system("cls");
    #else
        system("clear");
    #endif
    }
}