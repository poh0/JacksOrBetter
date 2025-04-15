#include "HandEvaluator.hpp"

HandRank HandEvaluator::evaluateHand(const Hand& hand) {
    if (isRoyalFlush(hand)) return HandRank::RoyalFlush;
    if (isStraightFlush(hand)) return HandRank::StraightFlush;
    if (isFourOfAKind(hand)) return HandRank::FourOfAKind;
    if (isFullHouse(hand)) return HandRank::FullHouse;
    if (isFlush(hand)) return HandRank::Flush;
    if (isStraight(hand)) return HandRank::Straight;
    if (isThreeOfAKind(hand)) return HandRank::ThreeOfAKind;
    if (isTwoPair(hand)) return HandRank::TwoPair;
    if (isJacksOrBetter(hand)) return HandRank::OnePairJacksOrBetter;
    return HandRank::HighCard; // Default case
}

bool HandEvaluator::isRoyalFlush(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isStraightFlush(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isFourOfAKind(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isFullHouse(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isFlush(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isStraight(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isThreeOfAKind(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isTwoPair(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isJacksOrBetter(const Hand &hand)
{
    return false;
}

bool HandEvaluator::isHighCard(const Hand &hand)
{
    return false;
}
