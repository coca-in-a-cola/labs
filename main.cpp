#include <iostream>
#include <locale>
#include "Hammurabi/Hammurabi.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    return Hammurabi::main();
}
