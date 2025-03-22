#pragma once
#include <vector>
#include "Card.hpp"
#include <random>

class Deck {
public:
    Deck();

    void shuffle();

    // returns a card popped from deck, no copies are made
    Card dealCard();

    void initializeDeck();

private:
    std::vector<Card> m_Cards;

    // random number generator
    std::random_device rd;
    std::mt19937 rng{rd()};

};