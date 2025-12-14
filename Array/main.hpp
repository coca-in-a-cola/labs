#pragma once

#include "Array.hpp"
#include "../Shared/Helpers.h"

namespace YAR {
    int main(int argc, char **argv) {
        Array<int> a(1);
        a.insert(10);
        a.insert(20);
        a.insert(30);
        a.insert(40);
        a.insert(50);
        Helpers::prints(a.to_string());
        Helpers::prints("запустите через google tests, чтобы увидеть тесты");
        return 0;
    }
}