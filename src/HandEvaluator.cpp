#include "HandEvaluator.hpp"
#include "HandRankTable.hpp"

#include <map>
#include <bitset>

HandRank HandEvaluator::evaluateHand(Hand& hand)
{

    uint32_t handAsInt = handToUint32(hand);

    HandRank rankNoFlush = handRankTable.find(handAsInt)->second;

    if (isFlush(hand)) {
        if (rankNoFlush == HandRank::Straight) {
            return HandRank::StraightFlush;
        }
        else if (rankNoFlush == HandRank::RoyalStraight) {
            return HandRank::RoyalFlush;
        }
        else if ( (rankNoFlush != HandRank::FullHouse) || (rankNoFlush != HandRank::FourOfAKind)) {
            return HandRank::Flush;
        }
    }

    if (rankNoFlush == HandRank::RoyalStraight) {
        return HandRank::Straight;
    }

    return rankNoFlush; // Default case
}

std::vector<int> HandEvaluator::getAutoHoldIndicies(Hand &hand)
{
    std::map<int, int> valueFreqMap;

    std::vector<Card>& cards = hand.getCards();

    Suit firstSuit = cards[0].getSuit();
    int lowestVal = static_cast<int>(cards[0].getValue());

    bool isFlush = true;
    bool isStraight = true;

    for (int index = 0; index < 5; index++) {
        const Card& card = cards[index];
        int val = static_cast<int>(card.getValue());
        if (val < lowestVal) lowestVal = val;
        valueFreqMap[val]++;
    }

    // if no pairs occurred, straight and flush are possible
    if (valueFreqMap.size() > 4) {
        for (int index = 0; index < 5; index++) {
            const Card& card = cards[index];

            int val = static_cast<int>(card.getValue());
            if (isFlush && card.getSuit() != firstSuit) {
                isFlush = false;
            }

            if (isStraight) {
                if (val == 1) {
                    if (std::abs(val - lowestVal) > 4 || std::abs(14-lowestVal) > 4 || valueFreqMap[val] != 1) {
                        isStraight = false;
                        continue;
                    }        
                }
                if (std::abs(val - lowestVal) > 4 || valueFreqMap[val] != 1) {
                    isStraight = false;
                }
            }
        }
        if (isStraight || isFlush) {
            return std::vector<int>{0, 1, 2, 3, 4};
        } else {
            return {};
        }
    }

    std::vector<int> autoHoldidxs;
    autoHoldidxs.reserve(5);

    int firstLowPairValue = 0;
    int lowPairFirstIdx = -1;
    int lowPairSecondIdx = -1;
    bool shouldHoldLower = false;
    for (int index = 0; index < 5; index++) {
        const Card& card = cards[index];

        int val = static_cast<int>(card.getValue());
        int freq = valueFreqMap[val];

        bool lowPair = (freq == 2 && val < 11 && val != 1);
        bool jacksOrBetterPair = (freq == 2 && (val >= 11 || val == 1));
        bool threeOf = freq == 3;
        bool fourOf = freq == 4;

        if (jacksOrBetterPair || threeOf) {
            autoHoldidxs.push_back(index);
            if (firstLowPairValue) {
                autoHoldidxs.push_back(lowPairFirstIdx);
                if (lowPairSecondIdx != -1) autoHoldidxs.push_back(lowPairSecondIdx);
            }
            shouldHoldLower = true;
        }
        else if (lowPair && shouldHoldLower) {
            autoHoldidxs.push_back(index);
            if (firstLowPairValue) {
                autoHoldidxs.push_back(lowPairFirstIdx);
                autoHoldidxs.push_back(lowPairSecondIdx);
                firstLowPairValue = 0;
            }
        }
        else if (lowPair && !shouldHoldLower) {
            if (firstLowPairValue) {
                if (firstLowPairValue != val) {
                    autoHoldidxs.push_back(lowPairFirstIdx);
                    autoHoldidxs.push_back(index);
                    shouldHoldLower = true;
                    firstLowPairValue = 0;
                }
                lowPairSecondIdx = index;
                shouldHoldLower = true;
            } 
            else {
                firstLowPairValue = val;
                lowPairFirstIdx = index;
            }
        }
        else if (fourOf) {
            autoHoldidxs.push_back(index);
        }
    }

    return autoHoldidxs;
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
