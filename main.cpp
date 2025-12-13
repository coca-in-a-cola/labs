#include <iostream>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Shared/Helpers.h"
#include "Hammurabi/Hammurabi.h"

int main() {
    #ifdef _WIN32
        // Настройка консоли Windows на UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    std::locale::global(std::locale("en_US.UTF-8"));

    while (true) {
        auto labNumber = Helpers::input<val_t>("Введите номер лабораторной (1-4)");

        if (labNumber == 1) {
            return Hammurabi::main();
        }
    }
}
