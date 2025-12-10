#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string.h>

typedef int32_t val_t;

namespace Helpers {
    void drawFile(std::string filepath);

    void clearConsole();

    std::filesystem::path getFullPath(std::string& filepath);
    val_t randRange(val_t from, val_t to);

    template<typename T>
    void saveObject(T object, std::string& filepath) {
        auto fullPath = getFullPath(filepath);
        std::ofstream output_file(filepath, std::ios::binary);
        output_file.write((char*)&object, sizeof(object));
        output_file.close();
    }

    template<typename T>
    bool loadObject(T& outObject, std::string& filepath) {
        auto fullPath = getFullPath(filepath);
        std::ifstream input_file(fullPath, std::ios::binary);
        if (!input_file.is_open()) {
            return false;
        }
        input_file.read((char*)&outObject, sizeof(outObject));
        return true;
    }
    
}