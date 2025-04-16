#include "HandEvaluator.hpp"
#include "HandRankTable.hpp"

HandRank HandEvaluator::evaluateHand(Hand& hand) {

    uint32_t handAsInt = handToUint32(hand);

    HandRank rankNoFlush = handRankTable.find(handAsInt)->second;

    if (isFlush(hand)) {
        if (rankNoFlush == HandRank::Straight) {
            return HandRank::StraightFlush;
        }
        else if (rankNoFlush == HandRank::RoyalStraight) {
            return HandRank::RoyalFlush;
        }
        else if (rankNoFlush != HandRank::FullHouse | rankNoFlush != HandRank::FourOfAKind) {
            return HandRank::Flush;
        }
    }

    return rankNoFlush; // Default case
}

bool HandEvaluator::isFlush(Hand &hand)
{
    Suit firstSuit = hand.getCards()[0].getSuit();

    for (auto &card : hand.getCards()) {
        if (card.getSuit() != firstSuit) {
            return false;
        }
    }

    return true;
}

uint32_t HandEvaluator::handToUint32(Hand &hand)
{
    uint32_t hand_encoded = 1;
    for (auto &card : hand.getCards()) {
        hand_encoded*= rank_to_prime[static_cast<int>(card.getValue()) - 1];
    }
    return hand_encoded;
}
