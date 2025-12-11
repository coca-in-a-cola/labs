#pragma once

#include <span>
#include <cassert>
#include <utility>
#include <vector>
#include <stdint.h>
#include "GameData.h"

namespace Hammurabi {

    class Game {
    public:
        Game();
        
        void Load();
        void Run();
        void Save();
    private:
        GameData _data;
        InputData _inputData;

        void ProcessInput();
        bool ValidateInput();
        void Update();
        void Render();
        void PreUpdate();
        void RenderDeclineIncreace();
        bool _isRunning = true;
    };

    int main();
}