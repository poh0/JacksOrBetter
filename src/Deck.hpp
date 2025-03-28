#pragma once

#include <vector>
#include <random>

#include "Card.hpp"
#include "AnimationManager.hpp"
#include "Animation.hpp"

class Deck {
public:
    Deck(AnimationManager& animationManager);

    void shuffle();

    // returns a card popped from deck, no copies are made
    Card dealCard();

    void initialize();

    void setStackEffectPositions();

    void addShuffleAnimations();

    void addDealAnimations();

    void draw(sf::RenderWindow &window);

    void reset();

private:
    std::vector<Card> m_Cards;

    AnimationManager& mAnimationManager;

    // random number generator
    std::random_device rd;
    std::mt19937 rng{rd()};

};