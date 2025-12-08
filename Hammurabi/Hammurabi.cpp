#pragma once

#include <iostream>
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
            Render();
            ProcessInput();
            Update();
            _isRunning = false;
        }
    }

    void Game::ProcessInput() { }

    void Game::Update() { }

    void Game::Render() {
        Helpers::clearConsole();
        Helpers::drawFile("../data/render.txt");
        std::cout << "Мой повелитель, соизволь поведать тебе" << std::endl;
        std::cout << std::format("В году {} твоего высочайшего правления", _data.year) << std::endl;
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