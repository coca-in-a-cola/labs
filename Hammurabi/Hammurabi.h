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
        
        void ProcessInput();
        void Update();
        void Render();
        
        bool _isRunning = true;
    };

    int main();
}