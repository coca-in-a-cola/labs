#include <iostream>
#include <locale>

int main(int, char**){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::cout << "Привет на русском!\n";
    getchar();
    return 0;
}
