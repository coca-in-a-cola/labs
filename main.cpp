#include <iostream>
#include <locale>
#include "Hammurabi/Hammurabi.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
        // Настройка консоли Windows на UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    std::locale::global(std::locale("en_US.UTF-8"));

    return Hammurabi::main();
}
