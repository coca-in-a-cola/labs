#pragma once
#include <string>
#include "../Shared/Helpers.h"

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

    struct InputData {
        // Сколько акров прикажешь купить?
        val_t buyAcres;
        // Сколько бушелей пшеницы повелеваешь съесть?
        val_t eatBushels;
        // Сколько акров земли повелеваешь засеять?
        val_t plantAcres;
    };

    struct Stats {
        // Среднеготовой процент умерших от голода P
        float_t deathRate;
        // Количество акров земли на одного жителя L
        float_t acresPerCitizen;
        // общий рейтинг (обычно от 0 до 4)
        val_t grade;
    };
}