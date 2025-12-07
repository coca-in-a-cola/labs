#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <format>
#include "Helpers.h"

namespace Helpers {

    void drawFile(std::string filepath) {
        std::string content;
        auto fullPath = std::filesystem::current_path() / filepath;
        std::ifstream file(fullPath);

        if (!file.is_open()) {
            std::cout << std::format("file not found in filepath {}", fullPath.string()) << std::endl;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }
}