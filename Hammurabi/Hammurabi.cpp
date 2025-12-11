#pragma once

#include <iostream>
#include <cstdlib>
#include "Hammurabi.h"
#include "GameData.h"
#include "../Shared/Helpers.h"

namespace Hammurabi {

    Game::Game() {
        _data = GameData{};
        _inputData = InputData{};
    }

    void Game::Load() {
        GameData gameData;
        auto savedGamePath = std::string("../data/auto.save");
        auto isLoaded = Helpers::loadObject<GameData>(gameData, savedGamePath);

        if (isLoaded) {
            std::cout << "Загружена сохраненная игра";
            _data = gameData;
        } else {
            _data = initialGameData;
        }
    }

    void Game::Run() {
        while (_isRunning) {
            PreUpdate();
            Render();
            ProcessInput();
            Update();
        }
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
        val_t currentBushels = _data.wheatBushels
            - _inputData.buyAcres * _data.arcPrice
            - _inputData.plantAcres * 0.5f;

        if (currentBushels < 0) {
            return false;
        }

        if (_inputData.plantAcres > _data.population * 10) {
            return false;
        }

        return true;
    }

    void Game::PreUpdate() {
        auto arcPrice = Helpers::randRange(17, 26);
        _data.arcPrice = arcPrice;
    }

    void Game::Update() {

        GameData newData = {};

        newData.arces = _data.arces + _inputData.buyAcres;

        val_t currentBushels = _data.wheatBushels
            - _inputData.buyAcres * _data.arcPrice
            - _inputData.plantAcres * 0.5f;

        newData.fertility = Helpers::randRange(1, 6);
        newData.wheatIncreace = _inputData.plantAcres * newData.fertility;

        newData.decline = std::max(_data.population - _inputData.eatBushels / 20, 0);

        auto increace = newData.decline / 2 + (5 - newData.fertility) * currentBushels / 600 + 1;
        newData.increace = std::clamp(increace, 0, 50);

        newData.population = _data.population + newData.increace - newData.decline;

        newData.wheatBushels = currentBushels + newData.wheatIncreace;
        newData.pests = newData.wheatBushels * Helpers::randRange(.0f, 0.07f);
        newData.wheatBushels -= newData.pests;

        newData.is_plague = false;

        if (Helpers::randRange(1, 100) <= 15) {
            newData.is_plague = true;
            newData.population /= 2;
        }

        _data = newData;
    }

    void Game::Render() {
        Helpers::clearConsole();
        Helpers::drawFile("../data/render.txt");

        Helpers::printsh("Мой повелитель, соизволь поведать тебе");
        Helpers::prints("В году {} твоего высочайшего правления", _data.year);

        RenderDeclineIncreace();

        if (_data.is_plague) {
            std::cout << "Чума уничтожила половину населения!";
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
            std::cin.get();
            return 0;
        }
        catch (...) {
            std::cerr << "ERROR";
            return 1;
        }
    }
}