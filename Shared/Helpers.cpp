#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <format>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
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

    val_t randRange(val_t from, val_t to) {
        srand(static_cast <unsigned> (time(0)));
        return from + (rand() % (to - from));
    }

    float_t randRange(float_t from, float_t to) {
        srand(static_cast <unsigned> (time(0)));
        return from + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(to-from)));
    }

    void clearConsole() {
    #if defined(_WIN32) || defined(WIN32)
        system("cls");
    #else
        system("clear");
    #endif
    }
}