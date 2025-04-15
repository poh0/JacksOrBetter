#pragma once
#include <vector>
#include "Hand.hpp"

enum class HandRank {
    HighCard = 1,
    OnePairJacksOrBetter = 2,
    TwoPair = 3,
    ThreeOfAKind = 4,
    Straight = 5,
    Flush = 6,
    FullHouse = 7,
    FourOfAKind = 8,
    StraightFlush = 9,
    RoyalFlush = 10
};

class HandEvaluator {
public:
    static HandRank evaluateHand(const Hand& hand);
    
private:
    static bool isRoyalFlush(const Hand& hand);
    static bool isStraightFlush(const Hand& hand);
    static bool isFourOfAKind(const Hand& hand);
    static bool isFullHouse(const Hand& hand);
    static bool isFlush(const Hand& hand);
    static bool isStraight(const Hand& hand);
    static bool isThreeOfAKind(const Hand& hand);
    static bool isTwoPair(const Hand& hand);
    static bool isJacksOrBetter(const Hand& hand);
    static bool isHighCard(const Hand& hand);
};