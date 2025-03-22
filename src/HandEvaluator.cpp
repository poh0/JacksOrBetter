#include "HandEvaluator.hpp"

HandRank HandEvaluator::evaluateHand(const std::vector<Card>& hand) {
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

bool HandEvaluator::isRoyalFlush(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isStraightFlush(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isFourOfAKind(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isFullHouse(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isFlush(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isStraight(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isThreeOfAKind(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isTwoPair(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isJacksOrBetter(const std::vector<Card> &hand)
{
    return false;
}

bool HandEvaluator::isHighCard(const std::vector<Card> &hand)
{
    return false;
}
