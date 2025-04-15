#pragma once
#include <vector>
#include "Card.hpp"

class Hand {
public:
    Hand();
    void addCard(Card&& card);
    void draw(sf::RenderWindow &window);

    std::vector<Card>& getCards();

private:
    std::vector<Card> mCards;

};