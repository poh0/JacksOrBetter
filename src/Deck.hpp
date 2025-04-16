#pragma once

#include <vector>
#include <random>

#include "Card.hpp"
#include "AnimationManager.hpp"
#include "Animation.hpp"

class Deck {
public:
    Deck();

    void shuffle();

    void addCard(Card&& card);

    // returns a card popped from deck, no copies are made
    Card dealCard();

    void initialize();

    void draw(sf::RenderWindow &window);

    void reset();

public:
    std::vector<Card>& getCards();

private:
    std::vector<Card> m_Cards;

    // random number generator
    std::random_device rd;
    std::mt19937 rng{rd()};

};