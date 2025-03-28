#include "Game.hpp"

Game::Game(AnimationManager& animationManager) 
    : mState(GameState::WaitingToStart), mPlayerCredits(Config::STARTING_CREDITS),
    mAnimationManager(animationManager), mDeck(animationManager)
{
}

void Game::start()
{
    if (mState == GameState::WaitingToStart) {
        mDeck.initialize();
        mState = GameState::WaitingToDeal;
    }
}

void Game::dealHand()
{
    mState = GameState::Dealing;
    mDeck.shuffle();
    mDeck.setStackEffectPositions();
    mDeck.addShuffleAnimations();
}

void Game::draw(sf::RenderWindow &window)
{
    mDeck.draw(window);
}

GameState Game::getState() const
{
    return mState;
}

void Game::setState(GameState state)
{
    mState = state;
}
