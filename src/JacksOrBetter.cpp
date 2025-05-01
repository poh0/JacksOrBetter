#include "JacksOrBetter.hpp"
#include "ResourceManager.hpp"

JacksOrBetter::JacksOrBetter() 
    : window(
        sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}), 
        "Jacks Or Better",
        (sf::Style::Titlebar | sf::Style::Close)
    ),
    mGame(Game(mAnimationManager, mEventBus)),
    mResManager(ResourceManager::getInstance()),
    backgroundSprite(sf::Sprite(mResManager.getTexture("background"))),
    pressAnyKeyText(sf::Text(mResManager.getFont("toxi"), "Press any key to start", 30)),
    mBalanceText(sf::Text(mResManager.getFont("toxi"), "Balance: ", 18)),
    mCreditsText(sf::Text(mResManager.getFont("toxi"), "", 18)),
    mBetText(sf::Text(mResManager.getFont("toxi"), "Bet: ", 18)),
    mBetSizeText(sf::Text(mResManager.getFont("toxi"), "", 18)),
    mInfoText(sf::Text(mResManager.getFont("toxi"), "", 16)),
    mDealBtn(UI::PushButton(mResManager.getTexture("dealbtn_idle"), mResManager.getTexture("dealbtn_click"))),
    mDoubleBtn(UI::PushButton(mResManager.getTexture("holdbtn_idle"), mResManager.getTexture("holdbtn_click"), 3.0f)),
    mCollectBtn(UI::PushButton(mResManager.getTexture("holdbtn_idle"), mResManager.getTexture("holdbtn_click"), 3.0f))
{
    window.setFramerateLimit(120);
    window.setKeyRepeatEnabled(false);
    initUI();
    subscribeEvents();
}

void JacksOrBetter::run()
{
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void JacksOrBetter::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            // Press any key to start game: 
            if (mGame.getState() == GameState::WaitingToStart) {
                mGame.start();
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                if (mGame.getState() == GameState::WaitingToDeal) {
                    mGame.dealHand();
                }

                if (mGame.getState() == GameState::SelectingCardsToKeep) {
                    mGame.discardUnkeptCards();
                }

                if ( (mGame.getState() == GameState::HandEndedLoss) || (mGame.getState() == GameState::HandEndedWin)) {
                    mGame.dealHand();
                }
            }
            
            switch (keyPressed->scancode) {
                case sf::Keyboard::Scancode::Num1:
                    mGame.toggleKeepCard(0);
                    break;
                case sf::Keyboard::Scancode::Num2:
                    mGame.toggleKeepCard(1);
                    break;
                case sf::Keyboard::Scancode::Num3:
                    mGame.toggleKeepCard(2);
                    break;
                case sf::Keyboard::Scancode::Num4:
                    mGame.toggleKeepCard(3);
                    break;
                case sf::Keyboard::Scancode::Num5:
                    mGame.toggleKeepCard(4);
                    break;
            }
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mGame.leftMouseClick(mousePos);

                for (auto* btn : mPushButtons) {
                    if (btn->contains(mousePos)) btn->onPress();
                }
            }
        }

        if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                for (auto* btn : mPushButtons) {
                    btn->onRelease(mousePos);
                }
            }
        }
    }
}

void JacksOrBetter::update(float deltatime)
{
    mAnimationManager.update(deltatime);
}

void JacksOrBetter::render()
{
    window.clear();
    window.draw(backgroundSprite);

    GameState state = mGame.getState();

    if (state == GameState::WaitingToStart) {
        window.draw(pressAnyKeyText);
    }

    if (state != GameState::WaitingToStart) {
        mDealBtn.draw(window);
        window.draw(mBalanceText);
        window.draw(mCreditsText);
        window.draw(mBetText);
        window.draw(mBetSizeText);

        if (state != GameState::Shuffling && state != GameState::Dealing && state != GameState::Discarding) {
            window.draw(mInfoText);
        }

        if (state == GameState::HandEndedWin) {
            mDoubleBtn.draw(window);
            mCollectBtn.draw(window);
        }
        else {
            for (auto& btn : mHoldBtn) {
                btn.draw(window);
            }
        }
    }
    mGame.draw(window);

    window.display();
}

void JacksOrBetter::subscribeEvents()
{
    mEventBus.subscribe(GameEvent::CreditsChanged, [this]() {
        this->mCreditsText.setString(std::to_string(mGame.getCredits()));
    });

    mEventBus.subscribe(GameEvent::DealAnimComplete, [this]() {
        this->mDealBtn.setActive(true);
        if (this->mGame.getState() == GameState::SelectingCardsToKeep) {
            for (auto& btn : this->mHoldBtn) {
                btn.setActive(true);
            }
            mInfoText.setString("Choose which cards to HOLD and press DEAL");
        }
    });

    mEventBus.subscribe(GameEvent::DealingCards, [this]() {
        for (auto& btn : this->mHoldBtn) {
            btn.setActive(false);
        }
    });

    mEventBus.subscribe(GameEvent::HandEndedLoss, [this]() {
        for (auto& btn : this->mHoldBtn) {
            btn.setActive(false);
        }
        mInfoText.setString("No win this time. Choose your BET and press DEAL");
    });

    mEventBus.subscribe(GameEvent::HandEndedWin, [this]() {
        mInfoText.setString("You win! GAMBLE or COLLECT?");
    });
}

void JacksOrBetter::initUI()
{
    /*
    *   SETUP TEXTS
    */
    sf::FloatRect textRect = pressAnyKeyText.getLocalBounds();
    pressAnyKeyText.setOrigin(textRect.getCenter());
    pressAnyKeyText.setPosition(window.getView().getCenter());

    mBalanceText.setPosition({250.0f, 40.0f});
    mCreditsText.setPosition({365.0f, 40.0f});
    mCreditsText.setString(std::to_string(mGame.getCredits()));
    mCreditsText.setFillColor(sf::Color::Yellow);
    mCreditsText.setCharacterSize(20);

    mBetText.setPosition({550.0f, 40.0f});
    mBetSizeText.setPosition({615.0f, 40.0f});
    mBetSizeText.setString(std::to_string(mGame.getBetSize()));
    mBetSizeText.setFillColor(sf::Color::Yellow);
    mBetSizeText.setCharacterSize(20);

    mInfoText.setPosition({425.0f, 310.0f});
    mInfoText.setOrigin(mInfoText.getLocalBounds().getCenter());
    mInfoText.setString("Choose your BET and press DEAL");

    /*
    *   SETUP BUTTONS
    */
    mDealBtn.setPosition({Config::DEALBTN_XPOS, Config::DEALBTN_YPOS});
    mDealBtn.setText("DEAL");
    mDealBtn.setCallback([this]() {
        if (mGame.getState() == GameState::WaitingToDeal ||
            mGame.getState() == GameState::HandEndedLoss ||
            mGame.getState() == GameState::HandEndedWin
        ) {
            mGame.dealHand();
            mCreditsText.setString(std::to_string(mGame.getCredits()));
        }
        else if (mGame.getState() == GameState::SelectingCardsToKeep) {
            mGame.discardUnkeptCards();
        }
    });
    mPushButtons.push_back(&mDealBtn);

    mHoldBtn.reserve(5);
    for (int i = 0; i < 5; i++) {
        mHoldBtn.emplace_back(UI::PushButton(
            mResManager.getTexture("holdbtn_idle"),
            mResManager.getTexture("holdbtn_click"),
            3.0f
        ));
        mHoldBtn[i].setText("HOLD");
        mHoldBtn[i].setPosition({Config::HAND_X_POS - 60.0f + (Config::HAND_X_OFFSET) * (float)i, 580.0f});

        mHoldBtn[i].setCallback([this, i]() {
            this->mGame.toggleKeepCard(i);
        });
        mPushButtons.push_back(&mHoldBtn[i]);
    }

    mDoubleBtn.setPosition({
        Config::HAND_X_POS - 60.0f + Config::HAND_X_OFFSET*2,
        580.0f
    });
    mDoubleBtn.setText("GAMBLE?");
    mPushButtons.push_back(&mDoubleBtn);

    mCollectBtn.setPosition({
        Config::HAND_X_POS - 60.0f + Config::HAND_X_OFFSET*3,
        580.0f
    });
    mCollectBtn.setText("COLLECT");
    mPushButtons.push_back(&mCollectBtn);
}
