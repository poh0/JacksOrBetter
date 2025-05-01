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
#include "EventBus.hpp"

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

    Game(AnimationManager& animationManager, EventBus& bus);

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

    void leftMouseClick(sf::Vector2f pos);

    GameState getState() const;
    void setState(GameState state);

    int getCredits() const;
    int getBetSize() const;

private:

    GameState mState;

    Deck mDeck;

    Hand mPlayerHand;
    HandRank mPlayerHandRank = HandRank::Unranked;

    std::bitset<5> mKeptCards;
    
    std::vector<Card> mDiscardPile;

    AnimationManager& mAnimationManager;
    EventBus& mEventBus;

    int mCredits;
    int mBetSize;
};