#pragma once

#include <span>
#include <cassert>
#include <utility>
#include <vector>
#include <stdint.h>
#include "Config.h"
#include "Structs.h"

namespace Hammurabi {
    class Game {
    public:
        Game();
        
        void Load();
        void Run();
        void Autosave();
    private:
        GameData _data;
        InputData _inputData;
        Stats _stats = { .0f, .0f, 0 };
        val_t _timeleft = GAME_DURATION;

        void ProcessInput();
        bool ValidateInput();
        void PostUpdate();
        void CheckCrit(const GameData& newData);
        void CalculateStats(const GameData& newData);

        void Update();
        void Render();
        void PreRender();
        void RenderDeclineIncreace();
        void Finish();
        bool _isRunning = true;
    };

    int main();
}