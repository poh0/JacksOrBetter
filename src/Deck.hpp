#pragma once
#include <vector>
#include "Card.hpp"

class Deck {
public:
    Deck();

    void shuffle();

    const Card& drawCard();
private:
    std::vector<Card> m_Cards;
};