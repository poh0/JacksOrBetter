#include "Card.hpp"



Card::Card(CardValue _val, Suit _suit, bool _facedown, sf::Texture& texture)
    :   mSuit(_suit), mValue(_val), mFaceDown(_facedown),
        mSprite(sf::Sprite(texture, (_facedown) ? getCardBackTextureRect() : getCardTextureRect(_val, _suit)))
        // ^^^^^^ if card is face down, we get the card back from spritesheet, and if not, we get the front ^^^^^^^
{

}

Card::Card() : mSprite(sf::Sprite(ResourceManager::getInstance().getTexture("cards"), getCardTextureRect(CardValue::Ace, Suit::Hearts))) {}

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
    window.draw(mSprite);
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

sf::IntRect Card::getCardBackTextureRect()
{
    return sf::IntRect(
        {13 * Config::CARD_WIDTH, 4 * Config::CARD_HEIGHT},
        {Config::CARD_WIDTH, Config::CARD_HEIGHT}
    );
}