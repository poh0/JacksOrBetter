#pragma once

#include <SFML/Graphics.hpp>

#include "Deck.hpp"
#include "Hand.hpp"
#include "Config.hpp"
#include "AnimationManager.hpp"
#include "MoveBehavior.hpp"

enum class GameState {
    WaitingToStart,
    WaitingToDeal,
    Shuffling,
    Dealing,
    SelectingCardsToKeep,
    Discarding,
    HandEndedWin,
    HandEndedLoss,
    Doubling,
    DoubleSuccess,
    DoubleTie,
    DoubleFail
};

class Game {
public:

    Game(AnimationManager& animationManager);

    void start();
    void initGame();
    void dealHand();

    void draw(sf::RenderWindow &window);

    void setStackEffectPositions();
    void addShuffleAnimations();
    void addDealAnimations();


    GameState getState() const;
    void setState(GameState state);

private:

    GameState mState;

    Deck mDeck;

    Hand mPlayerHand;

    AnimationManager& mAnimationManager;

    int mPlayerCredits;
};