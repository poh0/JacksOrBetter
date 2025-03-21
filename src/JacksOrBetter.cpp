#include "JacksOrBetter.hpp"
#include <iostream>

JacksOrBetter::JacksOrBetter() 
    : window(sf::VideoMode({1280, 720}), "Jacks Or Better", sf::Style::Titlebar | sf::Style::Close),
    backgroundSprite(backgroundTexture)
{
    backgroundTexture = sf::Texture("res/background.jpg");
    backgroundSprite = sf::Sprite(backgroundTexture);

    // resizeBackground(); // Scale on startup
}

void JacksOrBetter::run()
{
    while (window.isOpen()) {
        processEvents();
        update();
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
        // if (event->is<sf::Event::Resized>())
        //     resizeBackground();
    }
}

void JacksOrBetter::update()
{
}

void JacksOrBetter::render()
{
    window.clear();
    window.draw(backgroundSprite);
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
