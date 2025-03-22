#include "Deck.hpp"

Deck::Deck()
{
}

void Deck::shuffle()
{
    std::shuffle(m_Cards.begin(), m_Cards.end(), Deck::rng);
}

Card Deck::dealCard()
{
    // todo: if (m_Cards.empty()) {}
    Card dealtCard = std::move(m_Cards.back());
    m_Cards.pop_back();
    return dealtCard;
}

void Deck::initializeDeck()
{
    m_Cards.reserve(52);

    sf::Texture& cardTextureSheet = ResourceManager::getInstance().getTexture("cards");

    for (int suit = 1; suit <= 4; ++suit) {
        for (int value = 2; value <= 13; ++value) {
            m_Cards.emplace_back(static_cast<CardValue>(value), static_cast<Suit>(suit), false, cardTextureSheet);
        }
    }
}
