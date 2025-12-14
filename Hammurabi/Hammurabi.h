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
        
        void load();
        void run();
        void autosave();
    private:
        GameData _data;
        InputData _inputData;
        Stats _stats = { .0f, .0f, 0 };
        val_t _timeleft = GAME_DURATION;

        void processInput();
        bool validateInput();
        void postUpdate();
        void checkCrit(const GameData& newData);
        void calculateStats(const GameData& newData);

        void update();
        void render();
        void preRender();
        void renderDeclineIncreace();
        void finish();
        bool _isRunning = true;
    };

    int main();
}