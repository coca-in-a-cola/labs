#pragma once
#include <string>

typedef int32_t val_t;

namespace Hammurabi {
    // все статы даны строго на начало хода. три верхние валюты вычисляются последними
    struct GameData {
        // валюты
        val_t population;
        val_t wheatBushels;
        val_t arces;

        // номер года
        val_t year;
        // сколько человек умерло
        val_t decline;
        // сколько человек пришли в город
        val_t increace;
        // цена за акр земли
        val_t arcPrice;
        // сколько пшеницы было собрано
        val_t wheatIncreace;
        // сколько бушелей пшеницы будет собрано с 1 акра
        val_t fertility;
        // сколько будет крыс (каждая крыса съест 1 бушель пшеницы)
        val_t pests;
        // есть ли чума в этом году
        bool is_plague;
    };

    constexpr GameData initialGameData = { 100, 2800, 1000, 1, 0, 0, 0, 0, 0, 0, false };
}