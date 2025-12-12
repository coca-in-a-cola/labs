#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string.h>
#include <chrono>
#include <thread>

typedef int32_t val_t;
typedef float float_t;
constexpr val_t PRINTS_DELAY_MS = 10;

namespace Helpers {
    void drawFile(std::string filepath);

    void clearConsole();

    std::filesystem::path getFullPath(const std::string& filepath);
    bool removeFile(const std::string filepath);
    val_t randRange(val_t from, val_t to);
    float_t randRange(float_t from, float_t to);
    std::string& ltrim(std::string& s);
    std::string& rtrim(std::string& s);
    std::string trim(std::string s);

    template<typename T>
    void saveObject(T object, std::string filepath) {
        auto fullPath = getFullPath(filepath);
        std::ofstream output_file(filepath, std::ios::binary);
        output_file.write((char*)&object, sizeof(object));
        output_file.close();
    }

    template<typename T>
    bool loadObject(T& outObject, std::string filepath) {
        auto fullPath = getFullPath(filepath);
        std::ifstream input_file(fullPath, std::ios::binary);
        if (!input_file.is_open()) {
            return false;
        }
        input_file.read((char*)&outObject, sizeof(outObject));
        return true;
    }

    template<typename... Args>
    void prints(const std::string& message, Args&&... args) {
        auto formatted = std::vformat(message, std::make_format_args(std::forward<Args>(args)...));

        for (char c : formatted) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(PRINTS_DELAY_MS));
        }

        std::cout << std::endl;
    }

    template<typename... Args>
    void printsh(const std::string& message, Args&&... args) {
        return prints("\033[3;42;30m" + message + "\033[0m\t\t", std::forward<Args>(args)...);
    }
    
    template<typename T>
    T input(std::string message = "") {
        if (!empty(message)) std::cout << message << " : ";
        T value;
        std::cin >> value;
        return value;
    }

}