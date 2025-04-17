#pragma once

#include <SFML/Graphics.hpp>

#include <bitset>

#include "Deck.hpp"
#include "Hand.hpp"
#include "Config.hpp"
#include "AnimationManager.hpp"
#include "MoveBehavior.hpp"
#include "RotationBehavior.hpp"
#include "HandEvaluator.hpp"

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

    void cleanup();

    void initGame();
    void dealHand();

    void discardUnkeptCards();

    void determineWin();

    void toggleKeepCard(int index);

    void draw(sf::RenderWindow &window);

    void setStackEffectPositions();
    void addShuffleAnimations();
    void addDealAnimations();
    void addKeepAnimation(int index, bool reverse = false, std::function<void()> callback = nullptr);

    GameState getState() const;
    void setState(GameState state);

private:

    GameState mState;

    Deck mDeck;

    Hand mPlayerHand;
    HandRank mPlayerHandRank = HandRank::Unranked;

    std::bitset<5> mKeptCards;
    
    std::vector<Card> mDiscardPile;

    AnimationManager& mAnimationManager;

    int mPlayerCredits;
};