#pragma once

#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "Card.hpp"


class JacksOrBetter {
public:
    JacksOrBetter();
    
    ~JacksOrBetter() {};
    
    void run();

private:
    void processEvents();
    void update();
    void render();
    //void resizeBackground();

    sf::RenderWindow window {};
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture {};
};