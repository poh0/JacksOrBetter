#include "Deck.hpp"

Deck::Deck()
{
}

void Deck::shuffle()
{
    std::shuffle(m_Cards.begin(), m_Cards.end(), Deck::rng);
}

void Deck::addCard(Card &&card)
{
    m_Cards.emplace_back(std::move(card));  // Moves instead of copying
}

Card Deck::dealCard()
{
    // todo: if (m_Cards.empty()) {}
    Card dealtCard = std::move(m_Cards.back());
    m_Cards.pop_back();
    return dealtCard;
}

void Deck::reset()
{

}

std::vector<Card>& Deck::getCards()
{
    // TODO: insert return statement here
    return m_Cards;
}

void Deck::initialize()
{
    m_Cards.reserve(52);

    sf::Texture& cardTextureSheet = ResourceManager::getInstance().getTexture("cards");

    for (int suit = 1; suit <= 4; suit++) {
        for (int value = 1; value <= 13; value++) {
            m_Cards.emplace_back(static_cast<CardValue>(value), static_cast<Suit>(suit), true, cardTextureSheet);
        }
    }

}

void Deck::draw(sf::RenderWindow &window)
{
    for (size_t i = 0; i < Config::CARDS_VISIBLE_IN_DECK; ++i) {
        window.draw(m_Cards[i].getSprite());
    }
}
