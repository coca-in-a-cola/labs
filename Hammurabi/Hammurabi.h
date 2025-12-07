#pragma once

#include <span>
#include <cassert>
#include <utility>
#include <vector>
#include <stdint.h>

typedef int32_t id_t;
constexpr id_t kIdUndef = 0;

namespace Hammurabi {

    struct GameData {
    };

    class Game {
    public:
        Game();
        
        void Initialize();
        void Initialize(GameData* gameData);

        void Run();

    private:
        GameData _data;
        
        void ProcessInput();
        void Update();
        void Render();
        
        bool _isRunning = true;
    };

    int main();
}