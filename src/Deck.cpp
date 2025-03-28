#include "Deck.hpp"
#include <iostream>

Deck::Deck(AnimationManager& animationManager) : mAnimationManager(animationManager)
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

void Deck::reset()
{
    
}

void Deck::initialize()
{
    m_Cards.reserve(52);

    sf::Texture& cardTextureSheet = ResourceManager::getInstance().getTexture("cards");

    for (int suit = 1; suit <= 4; ++suit) {
        for (int value = 2; value <= 13; ++value) {
            m_Cards.emplace_back(static_cast<CardValue>(value), static_cast<Suit>(suit), true, cardTextureSheet);
        }
    }

}

void Deck::setStackEffectPositions() {
    for (size_t i = std::max(0, (int)m_Cards.size() - 10); i < m_Cards.size(); ++i) {
        sw::Sprite3d& sprite = m_Cards[i].getSprite();
        sprite.setPosition({
            Config::DECK_XPOS + Config::DECK_STACK_X_OFFSET * (i - (m_Cards.size() - 5)),
            Config::DECK_YPOS + Config::DECK_STACK_Y_OFFSET * (i - (m_Cards.size() - 5))
        });
    }
}

void Deck::addShuffleAnimations()
{
    sf::Vector2f deltaX{75.0f, 0.0f};
    for (size_t i = std::max(0, (int)m_Cards.size() - 10); i < m_Cards.size(); ++i) {
        sw::Sprite3d& sprite = m_Cards[i].getSprite();
        auto animation = std::make_unique<Animation>(
            sprite,
            sprite.getPosition(),
            (i % 2) ? (sprite.getPosition() + deltaX) : (sprite.getPosition() - deltaX),
            0.5f*(i - std::max(0, (int)m_Cards.size() - 10)),
            1.5f
        );

        // we set a callback for the last animation to fire the dealing animations
        if (i == m_Cards.size() - 1) {
            animation->setCallback([this]() { addDealAnimations(); });
        }
        mAnimationManager.addAnimation(std::move(animation));
    }
}

void Deck::addDealAnimations()
{
    std::cout << "Firing deals" << std::endl;
}

void Deck::draw(sf::RenderWindow &window)
{
    for (size_t i = std::max(0, (int)m_Cards.size() - 10); i < m_Cards.size(); ++i) {
        window.draw(m_Cards[i].getSprite());
    }
}
