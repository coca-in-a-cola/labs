#pragma once

#include <iostream>
#include "Hammurabi.h"
#include "../Shared/Helpers.h"

namespace Hammurabi {

    Game::Game() {
        _data = GameData{};
    }

    void Game::Initialize() {
        Initialize(nullptr);
    }

    void Game::Initialize(GameData* gameData) {
        if (gameData) {
            _data = *gameData;
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
			Helpers::drawFile("../data/main.txt");

            auto game = Game();
            game.Initialize();
        
            std::cin.get();
            return 0;
        }
        catch (...) {
            std::cerr << "ERROR" << std::endl;
            return 1;
        }
    }
}