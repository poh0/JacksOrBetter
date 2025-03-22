#pragma once
#include <vector>
#include "Card.hpp"

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
    static HandRank evaluateHand(const std::vector<Card>& hand);
    
private:
    static bool isRoyalFlush(const std::vector<Card>& hand);
    static bool isStraightFlush(const std::vector<Card>& hand);
    static bool isFourOfAKind(const std::vector<Card>& hand);
    static bool isFullHouse(const std::vector<Card>& hand);
    static bool isFlush(const std::vector<Card>& hand);
    static bool isStraight(const std::vector<Card>& hand);
    static bool isThreeOfAKind(const std::vector<Card>& hand);
    static bool isTwoPair(const std::vector<Card>& hand);
    static bool isJacksOrBetter(const std::vector<Card>& hand);
    static bool isHighCard(const std::vector<Card>& hand);
};