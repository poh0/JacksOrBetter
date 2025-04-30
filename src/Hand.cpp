#include "Hand.hpp"

Hand::Hand()
{
    mCards.reserve(5);
}

void Hand::addCard(Card &&card)
{
    mCards.emplace_back(std::move(card));  // Moves instead of copying
}

void Hand::draw(sf::RenderWindow &window)
{
    // Render in reverse order
    for (auto it = mCards.rbegin(); it != mCards.rend(); ++it) {
        window.draw(it->getSprite());
    }
}

std::vector<Card> &Hand::getCards()
{
    return mCards;
}

Card Hand::moveCard()
{
    // todo: if (m_Cards.empty()) {}
    Card dealtCard = std::move(mCards.back());
    mCards.pop_back();
    return dealtCard;
}
