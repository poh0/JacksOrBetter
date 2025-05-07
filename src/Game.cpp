#include "Game.hpp"
#include <iostream>

const std::unordered_map<HandRank, int> Game::mPayoutTable = {
    { HandRank::Unranked, 0 },
    { HandRank::OnePairJacksOrBetter, 1 },
    { HandRank::TwoPair, 2 },
    { HandRank::ThreeOfAKind, 3 },
    { HandRank::Straight, 4 },
    { HandRank::Flush, 6 },
    { HandRank::FullHouse, 9 },
    { HandRank::FourOfAKind, 25},
    { HandRank::StraightFlush, 50 },
    { HandRank::RoyalFlush, 800 }
};

const std::unordered_map<HandRank, std::string> Game::mHandRankStr = {
    { HandRank::OnePairJacksOrBetter, "Jacks or Better" },
    { HandRank::TwoPair, "Two Pair" },
    { HandRank::ThreeOfAKind, "Three of a Kind" },
    { HandRank::Straight, "Straight" },
    { HandRank::Flush, "Flush" },
    { HandRank::FullHouse, "Full House" },
    { HandRank::FourOfAKind, "Four of a Kind"},
    { HandRank::StraightFlush, "Straight Flush" },
    { HandRank::RoyalFlush, "Royal Flush" }
};

Game::Game(AnimationManager& animationManager, EventBus& bus) 
    : mState(GameState::WaitingToStart), mCredits(Config::STARTING_CREDITS),
    mAnimationManager(animationManager), mEventBus(bus),
    mDeck(), mKeptCards(0b00000), mBetSize(Config::DEFAULT_BET), mCurrentWin(0)
{
    mDiscardPile.reserve(5);
}

void Game::start()
{
    if (mState == GameState::WaitingToStart) {
        mDeck.initialize();
        mDeck.shuffle();
        setStackEffectPositions();
        mState = GameState::WaitingToDeal;
    }
}

void Game::cleanup()
{
    // move cards from discard pile back to the deck
    if (mDiscardPile.size() > 0) {
        for (auto &card : mDiscardPile) {
            card.flipCard();
            mDeck.addCard(std::move(card));
        }
        mDiscardPile.clear();
    }

    // move cards from hand back to the deck
    for (int i = 0; i < 5; i++) {
        Card poppedCard = mPlayerHand.moveCard();
        poppedCard.flipCard();
        mDeck.addCard(std::move(poppedCard));
    }
}

void Game::dealHand(bool doubling)
{
    if (mCredits < mBetSize) {
        return;
    }

    mCredits -= mBetSize;

    if ( (mState == GameState::DoubleFail) || (mState == GameState::HandEndedLoss) || (mState == GameState::HandEndedWin) || mState == GameState::CollectedWin ) {
        cleanup();
    }
    mState = GameState::Shuffling;
    mDeck.shuffle();
    Game::setStackEffectPositions();

    // We add cards to the hand before adding shuffle anims,
    // because last shuffle anim will have callback on addDealAnimations(),
    // which assumes there will be cards on mPlayerHand.
    // We can do this because the rendered cards are the first 4 cards of the deck,
    // and those moved to the mPlayerHand are the LAST five cards.
    for (int i = 0; i < 5; i++)
    {
        mPlayerHand.addCard(mDeck.dealCard());
    }

    Game::addShuffleAnimations();
    mEventBus.emit(GameEvent::CreditsChanged);
    mEventBus.emit(GameEvent::DealingCards);
}

void Game::discardUnkeptCards()
{
    mState = GameState::Discarding;
    auto& playerCards = mPlayerHand.getCards();

    if (mKeptCards.all()) {
        for (int i = playerCards.size() - 1; i >= 1; i--) {
            addKeepAnimation(i, true);
        }

        // We want a callback for the last move animation
        addKeepAnimation(0, true, [this]() {
            determineWin();
        });

        mKeptCards.reset();
        return;
    }

    for (int i = playerCards.size() - 1; i >= 0; i--) {
        if (!mKeptCards[i]) {
            mDiscardPile.push_back(std::move(playerCards[i]));
            playerCards.erase(playerCards.begin() + i);
            playerCards.insert(playerCards.begin() + i, std::move(mDeck.dealCard()));
        } else {
            addKeepAnimation(i, true);
        }
    }

    addDealAnimations();
    mKeptCards.reset(); // reset mKeptCards to all 0 (false)
    mEventBus.emit(GameEvent::DealingCards);
}

void Game::determineWin()
{
    mPlayerHandRank = HandEvaluator::evaluateHand(mPlayerHand);

    if (mPlayerHandRank == HandRank::Unranked) {
        mState = GameState::HandEndedLoss;
        mEventBus.emit(GameEvent::HandEndedLoss);
    } else {
        mState = GameState::HandEndedWin;
        mCurrentWin = getWinSize(mPlayerHandRank);
        mEventBus.emit(GameEvent::HandEndedWin);
    }
}

void Game::toggleKeepCard(int index)
{
    if (mState != GameState::SelectingCardsToKeep || index > 4 || index < 0) {
        return;
    }

    mKeptCards[index] = !mKeptCards[index];

    addKeepAnimation(index, !mKeptCards[index]);
}

void Game::collectWinnings()
{
    if (mState != GameState::HandEndedWin && mState != GameState::DoubleSuccess) return;
    mCredits += mCurrentWin;
    mState = GameState::CollectedWin;
}

void Game::dealDoublingHand()
{
    cleanup();
    mState = GameState::Shuffling;
    mDeck.shuffle();
    Game::setStackEffectPositions();

    // We add cards to the hand before adding shuffle anims,
    // because last shuffle anim will have callback on addDealAnimations(),
    // which assumes there will be cards on mPlayerHand.
    // We can do this because the rendered cards are the first 4 cards of the deck,
    // and those moved to the mPlayerHand are the LAST five cards.
    for (int i = 0; i < 5; i++)
    {
        mPlayerHand.addCard(mDeck.dealCard());
    }

    Game::addShuffleAnimations(true);
}

void Game::selectGambleCard(int index)
{
    if (mState != GameState::Doubling || index < 1 || index > 4) return;

    // Add slow flip anim (two anims).
    sw::Sprite3d& sprite = mPlayerHand.getCards()[index].getSprite();
    auto anim1 = std::make_unique<Animation>(
        sprite,
        std::make_unique<RotationBehavior>(
            sprite.getRotation3d(),
            sf::Vector3f{0.0f, 100.0f, 0.0f}
        ),
        0.0f,
        0.8f
    );

    auto anim2 = std::make_unique<Animation>(
        sprite,
        std::make_unique<RotationBehavior>(
            sf::Vector3f{0.0f, 100.0f, 0.0f},
            sf::Vector3f{0.0f, 0.0f, 0.0f}
        ),
        0.8f,
        0.1f
    );

    anim2->setCallback([this, index]() {
        auto& hand = mPlayerHand.getCards();
        if (hand[0] < hand[index]) {
            this->mState = GameState::DoubleSuccess;
            mCurrentWin *= 2;
            mEventBus.emit(GameEvent::DoubleSuccess);
        } else if (hand[0] > hand[index]) {
            this->mState = GameState::DoubleFail;
            mEventBus.emit(GameEvent::DoubleFailed);
        } else {
            this->mState = GameState::DoubleSuccess;

            // Temporarily treat tie as a success without incrementing currentWin
            mEventBus.emit(GameEvent::DoubleSuccess);
        }
    });
    mAnimationManager.addAnimation(std::move(anim1));
    mAnimationManager.addAnimation(std::move(anim2));
}

void Game::determineGambleResult(int index)
{
}

void Game::draw(sf::RenderWindow &window)
{
    if (mState == GameState::WaitingToStart)
    {
        return;
    }

    mDeck.draw(window);

    if ((mState == GameState::CollectedWin) ||
        (mState == GameState::Dealing) ||
        (mState == GameState::SelectingCardsToKeep) ||
        (mState == GameState::HandEndedLoss) ||
        (mState == GameState::Discarding) ||
        (mState == GameState::Doubling) ||
        (mState == GameState::DoubleSuccess) ||
        (mState == GameState::DoubleFail) ||
        (mState == GameState::DoubleTie) ||
        (mState == GameState::HandEndedWin))
    {
        mPlayerHand.draw(window);
    }

}

void Game::setStackEffectPositions() {
    for (size_t i = 0; i < Config::CARDS_VISIBLE_IN_DECK; ++i) {
        sw::Sprite3d& sprite = mDeck.getCards()[i].getSprite();
        sprite.setPosition({
            Config::DECK_XPOS + Config::DECK_STACK_X_OFFSET * i,
            Config::DECK_YPOS + Config::DECK_STACK_Y_OFFSET * i
        });
    }

    for (size_t i = Config::CARDS_VISIBLE_IN_DECK; i < mDeck.getCards().size(); ++i) {
        sw::Sprite3d& sprite = mDeck.getCards()[i].getSprite();
        sprite.setPosition({
            Config::DECK_XPOS + Config::DECK_STACK_X_OFFSET * (Config::CARDS_VISIBLE_IN_DECK - 1),
            Config::DECK_YPOS + Config::DECK_STACK_Y_OFFSET * (Config::CARDS_VISIBLE_IN_DECK - 1)
        });
    }
}

void Game::addShuffleAnimations(bool doubling)
{
    sf::Vector2f deltaX{170.0f, 0.0f};
    sf::Vector2f deltaY{0.0f, 20.0f};

    sf::Vector2f bottomSpritePos = mDeck.getCards()[0].getSprite().getPosition();
    for (size_t i = 1; i < Config::CARDS_VISIBLE_IN_DECK; ++i) {

        sw::Sprite3d& sprite = mDeck.getCards()[i].getSprite();

        sf::Vector2f newPos = sprite.getPosition() - deltaX + deltaY;
        sf::Vector2f oldPos = sprite.getPosition();

        auto animation = std::make_unique<Animation>(
            sprite,
            std::make_unique<MoveBehavior>(sprite.getPosition(), newPos),
            0.05f*i,
            Config::SHUFFLE_DURATION/2
        );

        auto animationReverse = std::make_unique<Animation>(
            sprite,
            std::make_unique<MoveBehavior>(
                newPos,
                bottomSpritePos + static_cast<float>(i) * sf::Vector2f{Config::DECK_STACK_X_OFFSET, Config::DECK_STACK_Y_OFFSET}
            ),
            0.05f*static_cast<float>(i) + Config::SHUFFLE_DURATION/2,
            Config::SHUFFLE_DURATION/2
        );

       // we set a callback for the last animation to fire the dealing animations

        if (i == Config::CARDS_VISIBLE_IN_DECK - 1) {
            animationReverse->setCallback([doubling, this]() {
                if (doubling) {
                    addDoubleDealAnims();
                } else {
                    addDealAnimations();
                }
                this->mState = GameState::Dealing;
            });
        }

        mAnimationManager.addAnimation(std::move(animation));
        mAnimationManager.addAnimation(std::move(animationReverse));
    }
}

// THis function will be fired by a callback of the last shuffling animation,
    // For each card in hand individually starting from the topmost rendered card on the hand (they'll be stacked on top of the deck)
    // We add the move animation and a flip animation
    // and for the last card animation, we set a callback that will set the game state to SelectingCardsToKeep
void Game::addDealAnimations()
{
    if (mKeptCards.all()) return;

    int lastAnimIdx = 4;
    for (lastAnimIdx; lastAnimIdx > 0; lastAnimIdx--) {
        if (!mKeptCards[lastAnimIdx]) {
            break;
        }
    }

    int idxForDelay = 0;
    for (size_t i = 0; i < mPlayerHand.getCards().size(); ++i) {
        if (mKeptCards[i]) {
            continue;
        }

        sw::Sprite3d& sprite = mPlayerHand.getCards()[i].getSprite();

        sf::Vector2f newPos = {
            Config::HAND_X_POS + (i * Config::HAND_X_OFFSET),
            Config::HAND_Y_POS
        };

        auto moveAnimation = std::make_unique<Animation>(
            sprite,
            std::make_unique<MoveBehavior>(
                sprite.getPosition(),
                newPos
            ),
            static_cast<float>(idxForDelay) * (Config::CARD_FLIP_DURATION + Config::CARD_MOVE_DURATION),
            Config::CARD_MOVE_DURATION
        );

        auto flipAnimation = std::make_unique<Animation>(
            sprite,
            std::make_unique<RotationBehavior>(
                sprite.getRotation3d(),
                sf::Vector3f{0.0f, 0.0f, 0.0f}
            ),
            (static_cast<float>(idxForDelay) * (Config::CARD_FLIP_DURATION + Config::CARD_MOVE_DURATION)) + Config::CARD_MOVE_DURATION,
            Config::CARD_MOVE_DURATION
        );

        if (i == lastAnimIdx) {
            flipAnimation->setCallback([&, this]() {
                if (this->mState == GameState::Dealing) {
                    this->mState = GameState::SelectingCardsToKeep;
                } else if (this->mState == GameState::Discarding) {
                    determineWin();
                }
                mEventBus.emit(GameEvent::DealAnimComplete);
            });
        }

        mAnimationManager.addAnimation(std::move(moveAnimation));
        mAnimationManager.addAnimation(std::move(flipAnimation));

        idxForDelay++;
    }
}

void Game::addKeepAnimation(int index, bool reverse, std::function<void()> callback)
{
    sw::Sprite3d &sprite = mPlayerHand.getCards()[index].getSprite();

    sf::Vector2f deltaY = {0.0f, (reverse ? -20.0f : 20.0f)};
    sf::Vector2f newPos = sprite.getPosition() + deltaY;

    auto moveAnimation = std::make_unique<Animation>(
        sprite,
        std::make_unique<MoveBehavior>(
            sprite.getPosition(),
            newPos
        ),
        0.0f,
        0.10f
    );

    // Optional callback
    if (callback) {
        moveAnimation->setCallback(callback);
    }

    mAnimationManager.addAnimation(std::move(moveAnimation));
}

void Game::addDoubleDealAnims()
{
    int idxForDelay = 0;
    for (size_t i = 0; i < mPlayerHand.getCards().size(); ++i) {
        sw::Sprite3d& sprite = mPlayerHand.getCards()[i].getSprite();

        sf::Vector2f newPos = {
            Config::HAND_X_POS + (i * Config::HAND_X_OFFSET),
            Config::HAND_Y_POS
        };

        auto moveAnimation = std::make_unique<Animation>(
            sprite,
            std::make_unique<MoveBehavior>(
                sprite.getPosition(),
                newPos
            ),
            static_cast<float>(idxForDelay) * (Config::CARD_FLIP_DURATION + Config::CARD_MOVE_DURATION),
            Config::CARD_MOVE_DURATION
        );

        if (i == mPlayerHand.getCards().size() - 1) {
            moveAnimation->setCallback([&, this]() {
                if (this->mState == GameState::Dealing) {
                    this->mState = GameState::Doubling;
                }
                mEventBus.emit(GameEvent::DealAnimComplete);
            });
        }

        if (idxForDelay == 0) {
            auto flipAnimation = std::make_unique<Animation>(
                sprite,
                std::make_unique<RotationBehavior>(
                    sprite.getRotation3d(),
                    sf::Vector3f{0.0f, 0.0f, 0.0f}
                ),
                (static_cast<float>(idxForDelay) * (Config::CARD_FLIP_DURATION + Config::CARD_MOVE_DURATION)) + Config::CARD_MOVE_DURATION,
                Config::CARD_MOVE_DURATION
            );
            mAnimationManager.addAnimation(std::move(flipAnimation));
        }

        mAnimationManager.addAnimation(std::move(moveAnimation));

        idxForDelay++;
    }
}

void Game::leftMouseClick(sf::Vector2f pos)
{
    if (mState == GameState::SelectingCardsToKeep) {
        int idx = 0;
        for (auto& card : mPlayerHand.getCards()) {
            if (card.contains(pos)) {
                toggleKeepCard(idx);
                break;
            }
            idx++;
        }
    }
    else if (mState == GameState::Doubling) {
        int idx = 0;
        for (auto& card : mPlayerHand.getCards()) {
            if (card.contains(pos)) {
                selectGambleCard(idx);
                break;
            }
            idx++;
        }
    }
}

GameState Game::getState() const
{
    return mState;
}

void Game::setState(GameState state)
{
    mState = state;
}

int Game::getCredits() const
{
    return mCredits;
}

int Game::getBetSize() const
{
    return mBetSize;
}

int Game::getWinSize(HandRank rank) const
{
    return mPayoutTable.at(rank) * mBetSize;
}

HandRank Game::getHandRank() const
{
    return mPlayerHandRank;
}

int Game::getCurrentWin() const
{
    return mCurrentWin;
}
