#pragma once
#include <string>
#include "Structs.h"

namespace Hammurabi {
    inline const std::string AUTOSAVE_LOCATION = "../data/auto.sav";

    static constexpr val_t GAME_DURATION = 3;

    static constexpr float_t SEED_COEF = .5f;
    static constexpr float_t DEATH_CRIT_COEF = .45f;

    static constexpr float_t PLAGUE_CHANCE = .15f;
    static constexpr float_t PLAGUE_MORTALITY = .5f;

    static constexpr val_t CULTIVATION = 10;
    static constexpr val_t WHEAT_CONSUMPTION = 20;

    static constexpr val_t FERTILITY_MIN = 1;
    static constexpr val_t FERTILITY_MAX = 6;

    static constexpr val_t ACR_PRICE_MIN = 0;
    static constexpr val_t ACR_PRICE_MAX = 50;

    static constexpr float_t PESTS_MIN = .0f;
    static constexpr float_t PESTS_MAX = .07f;

    inline constexpr GameData initialGameData = { 100, 2800, 1000, 1, 0, 0, 0, 0, 0, 0, false };

    // имхо с точки зрения геймдизайна надо выносить в конфиг не 4 магические константы, а небольшую функцию
    // чтобы было удобнее менять
    inline val_t INCREASE_F(const GameData& data) {
        return data.decline / 2
            + (5 - data.fertility) * data.wheatBushels / 600
            + 1;
    }
    
    static constexpr val_t INCREACE_MIN = 0;
    static constexpr val_t INCREACE_MAX = 50;

    inline constexpr GradeCondition GRADES_TABLE[] = {
        {0.33f, 7.0f},
        {0.10f, 9.0f},
        {0.03f, 10.0f},
    };

    inline constexpr Ending ENDINGS[] = {
        { 0, "../data/grade-0.txt", {
            "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас из города.",
            "Теперь вы вынуждены влачить жалкое существование в изгнании",
        } },
        { 1, "../data/grade-1.txt", {
            "Вы правили железной рукой, подобно Нерону и Ивану Грозному.",
            "Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем",
        } },
        { 2, "../data/grade-2.txt", {
            "Вы справились вполне неплохо",
            "У вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова",
        } },
        { 3, "../data/grade-3.txt", {
            "Фантастика!",
            "Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше",
        } },
    };

}