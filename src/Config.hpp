#pragma once

namespace Config {
    constexpr int CARD_WIDTH = 132;
    constexpr int CARD_HEIGHT = 192;
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr int FRAMERATE_LIMIT = 60;

    // todo: dynamic settings
    // settings
    constexpr bool ACE_IS_1_IN_GAMBLE = false; // Todo
    constexpr unsigned int STARTING_CREDITS = 1000;

    //offsets
    constexpr float HAND_X_OFFSET = 160.0f;
    constexpr float DECK_STACK_Y_OFFSET = -5.0f;
    constexpr float DECK_STACK_X_OFFSET = -4.0f;

    constexpr int HAND_X_POS = 275;
    constexpr int HAND_Y_POS = 500;

    constexpr int DECK_YPOS = 200;
    constexpr int DECK_XPOS = 300;

    constexpr int CARDS_VISIBLE_IN_DECK = 4;

    constexpr float CARD_MOVE_DURATION = 0.2f;
    constexpr float CARD_FLIP_DURATION = 0.14f;
}