#pragma once

#include <SFML/Graphics.hpp>

#include <bitset>
#include <unordered_map>

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
    CollectedWin,
    Doubling,
    DoubleSuccess,
    DoubleTie,
    DoubleFail
};

class Game {
public:

    Game(AnimationManager& animationManager, EventBus& bus);

    // Game logic functions
    void start();
    void cleanup();
    void dealHand(bool doubling = false);
    void discardUnkeptCards();
    void determineWin();
    void toggleKeepCard(int index);
    void collectWinnings();
    void dealDoublingHand();
    void selectGambleCard(int index);
    void determineGambleResult(int index);

    // rendering
    void draw(sf::RenderWindow &window);

    // Animations
    void setStackEffectPositions();
    void addShuffleAnimations(bool doubling = false);
    void addDealAnimations();
    void addKeepAnimation(int index, bool reverse = false, std::function<void()> callback = nullptr);
    void addDoubleDealAnims();

    // input handling
    void leftMouseClick(sf::Vector2f pos);

    // getters & setters
    GameState getState() const;
    void setState(GameState state);
    int getCredits() const;
    int getBetSize() const;
    int getWinSize(HandRank rank) const;
    HandRank getHandRank() const;
    int getCurrentWin() const;
    const std::bitset<5>& getKeptBitset() const;

private:

    GameState mState;

    Deck mDeck;

    Hand mPlayerHand;
    HandRank mPlayerHandRank = HandRank::Unranked;

    std::bitset<5> mKeptCards;
    
    std::vector<Card> mDiscardPile;

    AnimationManager& mAnimationManager;
    EventBus& mEventBus;

    static const std::unordered_map<HandRank, int> mPayoutTable;
    static const std::unordered_map<HandRank, std::string> mHandRankStr;

    int mCredits;
    int mBetSize;
    int mCurrentWin;
};