#include "JacksOrBetter.hpp"
#include "ResourceManager.hpp"

JacksOrBetter::JacksOrBetter() 
    : window(
        sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}), 
        "Jacks Or Better",
        (sf::Style::Titlebar | sf::Style::Close)
    ),
    backgroundSprite(sf::Sprite(ResourceManager::getInstance().getTexture("background"))),
    pressAnyKeyText(sf::Text(ResourceManager::getInstance().getFont("toxi"), "Press any key to start", 30)),
    mGame(mAnimationManager),
    mResManager(ResourceManager::getInstance()),
    mDealBtn(UI::PushButton(mResManager.getTexture("dealbtn_idle"), mResManager.getTexture("dealbtn_click")))
{
    window.setFramerateLimit(120);
    window.setKeyRepeatEnabled(false);

    /*
    *   SETUP TEXTS
    */
    sf::FloatRect textRect = pressAnyKeyText.getLocalBounds();
    pressAnyKeyText.setOrigin(textRect.getCenter());
    pressAnyKeyText.setPosition(window.getView().getCenter());


    /*
    *   SETUP BUTTONS
    */
    mDealBtn.setPosition({Config::DEALBTN_XPOS, Config::DEALBTN_YPOS});
    mDealBtn.setText("DEAL");
    mDealBtn.setCallback([this]() {
        if ( mGame.getState() == GameState::WaitingToDeal ||
             mGame.getState() == GameState::HandEndedLoss ||
             mGame.getState() == GameState::HandEndedWin
        ) {
            mGame.dealHand();
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
    if ( mGame.getState() == GameState::WaitingToDeal ||
        mGame.getState() == GameState::HandEndedLoss ||
        mGame.getState() == GameState::HandEndedWin
        ) {
        mDealBtn.setActive(true);
    }
    else if (mGame.getState() == GameState::SelectingCardsToKeep) {
        mDealBtn.setActive(true);
        for (auto& btn : mHoldBtn) {
            btn.setActive(true);
        }
    } 
    else {
        mDealBtn.setActive(false);
        for (auto& btn : mHoldBtn) {
            btn.setActive(false);
        }
    }
}

void JacksOrBetter::render()
{
    window.clear();
    window.draw(backgroundSprite);

    if (mGame.getState() == GameState::WaitingToStart) {
        window.draw(pressAnyKeyText);
    }

    if (mGame.getState() != GameState::WaitingToStart) {
        mDealBtn.draw(window);
        for (auto& btn : mHoldBtn) {
            btn.draw(window);
        }
    }

    mGame.draw(window);

    window.display();
}