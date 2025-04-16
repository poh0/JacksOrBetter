#include "Card.hpp"

Card::Card(CardValue _val, Suit _suit, bool _facedown, sf::Texture& texture)
    :   mSuit(_suit), mValue(_val), mFaceDown(_facedown)
{
    mSprite = std::make_unique<sw::Sprite3d>(texture, getCardTextureRect(_val, _suit), texture, getCardBackTextureOffset());
    mSprite->setOrigin(mSprite->getGlobalBounds().getCenter());
    if (_facedown) { mSprite->setYaw(180.0f); }
}

Card::Card() : mSprite(std::make_unique<sw::Sprite3d>(ResourceManager::getInstance().getTexture("cards"), getCardTextureRect(CardValue::Ace, Suit::Hearts))) { }

Suit Card::getSuit() const
{
    return mSuit;
}

CardValue Card::getValue() const
{
    return mValue;
}

void Card::draw(sf::RenderWindow &window)
{
    window.draw(*mSprite);
}

sw::Sprite3d &Card::getSprite()
{
    return *mSprite;
}

void Card::flipCard()
{
    mSprite->setRotation3d({
        0.0f,
        180.0f,
        0.0f
    });
}

sf::IntRect Card::getCardTextureRect(CardValue value, Suit suit)
{
    using namespace Config;

    if (value == CardValue::Ace) {
        return sf::IntRect(
            {0, (static_cast<int>(suit)-1)  * CARD_HEIGHT}, // We cast to int because suit and value are enum class. 
            {CARD_WIDTH, CARD_HEIGHT}                       // Also -1 because suit start from 1
        );
    }
    else {
        return sf::IntRect(
            { (static_cast<int>(value)-1) * CARD_WIDTH, (static_cast<int>(suit) - 1) * CARD_HEIGHT},
            {CARD_WIDTH, CARD_HEIGHT}
        );
    }
}

const sf::Vector2i Card::getCardBackTextureOffset()
{
    return sf::Vector2i(
        {Config::CARD_WIDTH, 4 * Config::CARD_HEIGHT}
    );
}