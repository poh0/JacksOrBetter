#pragma once

namespace Config {
    constexpr int CARD_WIDTH = 79;
    constexpr int CARD_HEIGHT = 123;
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr int FRAMERATE_LIMIT = 60;

    // todo: dynamic settings
    // settings
    constexpr bool ACE_IS_1_IN_GAMBLE = false; // Todo
    constexpr unsigned int STARTING_CREDITS = 1000;

    //offsets
    constexpr float HAND_X_OFFSET = 150.0f;
}