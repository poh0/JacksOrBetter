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
    mGame(mAnimationManager)
{
    window.setFramerateLimit(120);
    // backgroundTexture = sf::Texture("res/background.jpg");
    // backgroundSprite = sf::Sprite(backgroundTexture);
    sf::FloatRect textRect = pressAnyKeyText.getLocalBounds();
    pressAnyKeyText.setOrigin(textRect.getCenter());
    pressAnyKeyText.setPosition(window.getView().getCenter());

    window.setKeyRepeatEnabled(false);

    // load spritesheet of cards
    //cardSheetTexture = sf::Texture("res/card_sheet.png");

    // resizeBackground(); // Scale on startup
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
            }
        }

        // if (event->is<sf::Event::Resized>())
        //     resizeBackground();
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

    if (mGame.getState() == GameState::WaitingToStart) {
        window.draw(pressAnyKeyText);
    }

    mGame.draw(window);

    window.display();
}

// void JacksOrBetter::resizeBackground()
// {
//     sf::Vector2u windowSize = window.getSize();
//     sf::Vector2u textureSize = backgroundTexture.getSize();

//     float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
//     float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

//     float scale = std::max(scaleX, scaleY);

//     backgroundSprite.setScale({scale, scale});
//     backgroundSprite.setPosition({
//         (windowSize.x - textureSize.x * scale) / 2,
//         (windowSize.y - textureSize.y * scale) / 2
//     });
// }
