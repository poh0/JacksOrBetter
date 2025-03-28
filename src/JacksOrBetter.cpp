#include "JacksOrBetter.hpp"
#include "ResourceManager.hpp"
#include <iostream>

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
    window.setFramerateLimit(Config::FRAMERATE_LIMIT);
    // backgroundTexture = sf::Texture("res/background.jpg");
    // backgroundSprite = sf::Sprite(backgroundTexture);
    sf::FloatRect textRect = pressAnyKeyText.getLocalBounds();
    pressAnyKeyText.setOrigin(textRect.getCenter());
    pressAnyKeyText.setPosition(window.getView().getCenter());
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
