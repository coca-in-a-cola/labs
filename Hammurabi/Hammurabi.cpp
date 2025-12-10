#pragma once

#include <iostream>
#include <cstdlib>
#include "Hammurabi.h"
#include "GameData.h"
#include "../Shared/Helpers.h"

namespace Hammurabi {

    Game::Game() {
        _data = GameData{};
    }

    void Game::Load() {
        GameData gameData;
        auto savedGamePath = std::string("../data/auto.save");
        auto isLoaded = Helpers::loadObject<GameData>(gameData, savedGamePath);

        if (isLoaded) {
            std::cout << "Загружена сохраненная игра" << std::endl;
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
            _isRunning = false;
        }
    }

    void Game::ProcessInput() { }

    void Game::PreUpdate() {
        auto arcPrice = Helpers::randRange(17, 26);
        _data.arcPrice = arcPrice;
    }

    void Game::Update() { }

    void Game::Render() {
        Helpers::clearConsole();
        Helpers::drawFile("../data/render.txt");

        std::cout << "Мой повелитель, соизволь поведать тебе" << std::endl;
        std::cout << std::format("В году {} твоего высочайшего правления", _data.year) << std::endl;

        RenderDeclineIncreace();

        if (_data.is_plague) {
            std::cout << "Чума уничтожила половину населения!" << std::endl;
        }

        std::cout << std::format("Население города сейчас составляет {} человек", _data.population) << std::endl;

        if (_data.wheatIncreace) {
            std::cout << std::format("Мы собрали {} бушелей пшеницы, по {} бушеля с акра", _data.wheatIncreace, _data.fertility) << std::endl;
        }

        if (_data.pests) {
            std::cout << std::format("Крысы истребили {} бушелей пшеницы, оставив {} бушеля в амбарах", _data.pests, _data.wheatBushels) << std::endl;
        }
        
        std::cout << std::format("Город сейчас занимает {} акров", _data.arces) << std::endl;
        std::cout << std::format("1 акр земли стоит сейчас {} бушель", _data.arcPrice) << std::endl;
    }

    void Game::RenderDeclineIncreace() {
        if (!_data.decline && !_data.increace) {
            return;
        }

        if (!_data.decline) {
            std::cout << std::format("{} человек прибыли в наш великий город", _data.increace) << std::endl;
            return;
        }

        if (!_data.increace) {
            std::cout << std::format("{} человек умелри с голоду", _data.decline) << std::endl;
            return;
        }

        std::cout << std::format("{} человек умелри с голоду, и {} человек прибыли в наш великий город", _data.decline, _data.increace) << std::endl;
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
            std::cerr << "ERROR" << std::endl;
            return 1;
        }
    }
}