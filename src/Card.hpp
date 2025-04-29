#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SelbaWard/Sprite3d.hpp>

#include "ResourceManager.hpp"
#include "Config.hpp"

enum class CardValue {
    Ace = 1,
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
    King
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

    sw::Sprite3d& getSprite();

    void flipCard();

    // Static functions to get the card texture rectangle from sprite sheet
    static sf::IntRect getCardTextureRect(CardValue value, Suit suit);
    static const sf::Vector2i getCardBackTextureOffset();

public:
    bool contains(sf::Vector2f pos) const; // for mouse click

private:
    // Suit of this card
    Suit mSuit;

    // Value of this card
    CardValue mValue;

    bool mFaceDown;

    std::unique_ptr<sw::Sprite3d> mSprite;
};