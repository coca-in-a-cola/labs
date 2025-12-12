#pragma once

#include <iostream>
#include <cstdlib>
#include "Config.h"
#include "Hammurabi.h"
#include "Structs.h"
#include "../Shared/Helpers.h"

namespace Hammurabi {

    Game::Game() {
        _data = GameData{};
        _inputData = InputData{};
    }

    void Game::Load() {
        GameData gameData;
        auto hasSave = Helpers::loadObject<GameData>(gameData, AUTOSAVE_LOCATION);

        if (hasSave) {
            Helpers::printsh("[Найдена сохраненная игра]");
            char c = Helpers::input<char>("Загрузить сохраненную игру? [y/n]");

            if (c == 'y' || c == 'Y') {
                _data = gameData;
                return;
            }
        }

        _data = initialGameData;
    }

    void Game::Autosave() {
        Helpers::saveObject<GameData>(_data, AUTOSAVE_LOCATION);
    }

    void Game::Run() {
        while (_isRunning) {
            PreRender();
            Render();
            ProcessInput();
            Update();
            PostUpdate();
            Autosave();
        }

        Finish();
    }

    void Game::ProcessInput() {
        Helpers::printsh("Что прикажешь, повелитель?");
        bool isValidInput = false;

        _inputData = InputData{};
        
        while(!isValidInput) {
            auto buyAcres = Helpers::input<val_t>("> Сколько акров земли повелеваешь купить?");
            auto eatBushels = Helpers::input<val_t>("> Сколько бушелей пшеницы повелеваешь съесть?");
            auto plantAcres = Helpers::input<val_t>("> Сколько акров земли повелеваешь засеять?");
            _inputData = { buyAcres, eatBushels, plantAcres };
            isValidInput = ValidateInput();

            if (!isValidInput) {
                Helpers::clearConsole();
                Helpers::drawFile("../data/pray.txt");
                Helpers::printsh(
                    "О, повелитель, пощади нас! У нас только {} человек, {} бушелей пшшеницы и {} акров земли!",
                    _data.population,
                    _data.wheatBushels,
                    _data.arces
                );
            }
        }
    }

    bool Game::ValidateInput() {
        if (_inputData.buyAcres < 0 || _inputData.plantAcres < 0 || _inputData.eatBushels < 0) {
            return false;
        }

        val_t currentBushels = _data.wheatBushels
            - _inputData.eatBushels
            - _inputData.buyAcres * _data.arcPrice
            - _inputData.plantAcres * SEED_COEF;
        
        if (currentBushels < 0) {
            return false;
        }

        if (_inputData.plantAcres > _data.population * CULTIVATION) {
            return false;
        }

        return true;
    }

    void Game::PreRender() {
        auto arcPrice = Helpers::randRange(INCREACE_MIN, INCREACE_MAX);
        _data.arcPrice = arcPrice;
    }

    void Game::Update() {

        GameData newData = {};

        newData.arces = _data.arces + _inputData.buyAcres;

        newData.wheatBushels = _data.wheatBushels
            - _inputData.eatBushels
            - _inputData.buyAcres * _data.arcPrice
            - _inputData.plantAcres * SEED_COEF;

        newData.fertility = Helpers::randRange(FERTILITY_MIN, FERTILITY_MAX);
        newData.wheatIncreace = _inputData.plantAcres * newData.fertility;

        newData.decline = std::max(_data.population - _inputData.eatBushels / WHEAT_CONSUMPTION, 0);

        auto increace = INCREASE_F(newData);
        newData.increace = std::clamp(increace, INCREACE_MIN, INCREACE_MAX);

        newData.population = _data.population + newData.increace - newData.decline;

        newData.wheatBushels += newData.wheatIncreace;
        newData.pests = newData.wheatBushels * Helpers::randRange(PESTS_MIN, PESTS_MAX);
        newData.wheatBushels -= newData.pests;

        newData.is_plague = false;

        if (Helpers::randRange(.0f, 1.0f) <= PLAGUE_CHANCE) {
            newData.is_plague = true;
            newData.population *= PLAGUE_MORTALITY;
        }

        CheckCrit(newData);
        CalculateStats(newData);
        newData.year = ++_data.year;
        _data = newData;
    }

    void Game::PostUpdate() {
        if (!_timeleft) {
            _isRunning = false;
        }
    }

    void Game::CheckCrit(const GameData& newData) {
        if (newData.decline >= _data.population * DEATH_CRIT_COEF) {
            _isRunning = false;
        }
    }

    void Game::CalculateStats(const GameData& newData) {
        float_t currentDeathRate = newData.decline / _data.population;
        float_t acresPerCitizen = newData.arces / _data.population ;
        
        float_t deathRate = (_stats.deathRate * (_data.year - 1) + currentDeathRate) / _data.year;

        val_t grade = 0;

        if (--_timeleft) {
            _stats = { deathRate, acresPerCitizen, grade };
            return;
        }

        for (const auto& rule : GRADES_TABLE) {
            if (deathRate <= rule.maxDeathRate && acresPerCitizen >= rule.minAcresPerCitizen) ++grade;
        }

        _stats = { deathRate, acresPerCitizen, grade };
    }

    void Game::Finish() {
        Helpers::clearConsole();
        Helpers::removeFile(AUTOSAVE_LOCATION);

        const Ending* ending = nullptr;
        for (const auto& e : ENDINGS) {
            if (e.grade == _stats.grade) {
                ending = &e;
                break;
            }
        }

        if (!ending) {
            ending = &ENDINGS[0];
        }

        Helpers::drawFile(std::string(ending->image));
        for (auto line : ending->lines) {
            Helpers::printsh(std::string(line));
        }

        char c = Helpers::input<char>("Игра окончена. Ваши последние слова");
    }

    void Game::Render() {
        Helpers::clearConsole();
        Helpers::drawFile("../data/render.txt");

        Helpers::printsh("Мой повелитель, соизволь поведать тебе");
        Helpers::prints("В году {} твоего высочайшего правления", _data.year);

        RenderDeclineIncreace();

        if (_data.is_plague) {
            Helpers::printsh("Чума уничтожила половину населения!");
        }

        Helpers::prints("Население города сейчас составляет {} человек", _data.population);

        if (_data.wheatIncreace) {
            Helpers::prints("Мы собрали {} бушелей пшеницы, по {} бушеля с акра", _data.wheatIncreace, _data.fertility);
        }

        if (_data.pests) {
            Helpers::prints("Крысы истребили {} бушелей пшеницы, оставив {} бушеля в амбарах", _data.pests, _data.wheatBushels);
        } else {
            Helpers::prints("В амбарах сейчас {} бушеля пшеницы", _data.wheatBushels);
        }
        
        Helpers::prints("Город сейчас занимает {} акров", _data.arces);
        Helpers::prints("1 акр земли стоит сейчас {} бушель", _data.arcPrice);
    }

    void Game::RenderDeclineIncreace() {
        if (!_data.decline && !_data.increace) {
            return;
        }

        if (!_data.decline) {
            Helpers::prints("{} человек прибыли в наш великий город", _data.increace);
            return;
        }

        if (!_data.increace) {
            Helpers::prints("{} человек умелри с голоду", _data.decline);
            return;
        }

        Helpers::prints("{} человек умелри с голоду, и {} человек прибыли в наш великий город", _data.decline, _data.increace);
    }

    int main() {
        try {
            auto game = Game();
            Helpers::drawFile("../data/main.txt");
            std::cin.get();

            game.Load();
            game.Run();
            return 0;
        }
        catch (...) {
            std::cerr << "ERROR";
            return 1;
        }
    }
}