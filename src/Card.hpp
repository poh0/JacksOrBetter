#pragma once

#include <SFML/Graphics.hpp>
#include "JacksOrBetter.hpp"

enum class CardValue {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

// These are in the same order as in the sprite sheet
enum class Suit {
    Clubs = 1,
    Diamonds,
    Hearts,
    Spades
};

class Card {
public:
    Card(CardValue _val, Suit _suit, bool _visible, sf::Texture &texture);
    Card();
    Suit getSuit() const;

    CardValue getValue() const;

    void draw(sf::RenderWindow& window);

    // Static functions to get the card texture rectangle from sprite sheet
    static sf::IntRect getCardTextureRect(CardValue value, Suit suit);
    static sf::IntRect getCardBackTextureRect();

private:
    // Suit of this card
    Suit mSuit;

    // Value of this card
    CardValue mValue;

    bool mFaceDown;

    sf::Sprite mSprite;

};