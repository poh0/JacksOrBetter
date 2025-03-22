#pragma once

#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "Deck.hpp"

class JacksOrBetter {
public:
    JacksOrBetter();
    
    ~JacksOrBetter() {};
    
    void run();

private:

    Deck deck;

    void processEvents();
    void update();
    void render();
    //void resizeBackground();

    sf::RenderWindow window {};
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture {};
};