#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"
#include "AnimationManager.hpp"
#include "PushButton.hpp"
#include "EventBus.hpp"

class JacksOrBetter {
public:
    JacksOrBetter();
    
    ~JacksOrBetter() {};
    
    void run();

private:
    void processEvents();
    void update(float deltatime);
    void render();
    void subscribeEvents();
    void initUI();

    sf::RenderWindow window {};

    Game mGame;
    AnimationManager mAnimationManager;
    ResourceManager& mResManager;
    EventBus mEventBus;

    sf::Sprite backgroundSprite;
    std::vector<sf::Sprite> mHeldIndicators;

    // TEXTS
    sf::Text pressAnyKeyText;
    sf::Text mBalanceText;
    sf::Text mCreditsText;
    sf::Text mBetText;
    sf::Text mBetSizeText;
    sf::Text mInfoText;

    // BUTTONS
    UI::PushButton mDealBtn;
    std::vector<UI::PushButton> mHoldBtn;
    UI::PushButton mDoubleBtn;
    UI::PushButton mCollectBtn;

    std::vector<UI::PushButton*> mPushButtons;
    // UI::PushButton mSettingsBtn
};