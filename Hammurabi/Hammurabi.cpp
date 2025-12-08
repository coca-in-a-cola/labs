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
            ProcessInput();
            Update();
            Render();
            _isRunning = false;
        }
    }

    void Game::ProcessInput() { }

    void Game::Update() { }

    void Game::Render() { }

    int main() {
        try {
            auto game = Game();

            Helpers::drawFile("../data/main.txt");
            std::cin.get();

            game.Load();
            std::cin.get();
            game.Run();
            return 0;
        }
        catch (...) {
            std::cerr << "ERROR" << std::endl;
            return 1;
        }
    }
}