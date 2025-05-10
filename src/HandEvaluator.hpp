#pragma once
#include <vector>
#include "Hand.hpp"

enum class HandRank {
    Unranked = 1,
    OnePairJacksOrBetter,
    TwoPair,
    ThreeOfAKind,
    Straight,
    RoyalStraight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};

class HandEvaluator {
public:
    static HandRank evaluateHand(Hand& hand);
    static std::vector<int> getAutoHoldIndicies(Hand& hand);

private:
    static bool isFlush(Hand& hand);

    static uint32_t handToUint32(Hand& hand);

    static inline constexpr std::array<uint32_t, 13> rank_to_prime = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41
        // index = static_cast<int>(Rank) where Rank is from 0..12
    };
};