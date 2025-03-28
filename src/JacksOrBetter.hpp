#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"
#include "AnimationManager.hpp"

class JacksOrBetter {
public:
    JacksOrBetter();
    
    ~JacksOrBetter() {};
    
    void run();

private:
    void processEvents();
    void update(float deltatime);
    void render();
    //void resizeBackground();
    
    sf::RenderWindow window {};
    sf::Sprite backgroundSprite;

    sf::Text pressAnyKeyText;

    Game mGame;

    AnimationManager mAnimationManager;

};