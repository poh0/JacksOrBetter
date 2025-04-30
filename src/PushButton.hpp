#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

namespace UI {
class PushButton {
public:

    PushButton(const sf::Texture& idleTexture, const sf::Texture& clickedTexture, float shift_y = 6.0f);

    void draw(sf::RenderWindow& renderWindow);

    bool contains(sf::Vector2f point) const;

    void setCallback(std::function<void()> callback);

    void setText(const std::string& text, unsigned int size = 15);
    void setPosition(sf::Vector2f pos);

    void onPress();
    void onRelease(sf::Vector2f mousePos);

    void setActive(bool active);

private:

    sf::Text mText;
    bool mHasText = false;

    const sf::Texture& mIdleTexture;
    const sf::Texture& mClickedTexture;

    sf::Sprite mSprite;

    bool mIsPressed = false;
    std::function<void()> mCallback;

    float mShiftY;

    bool mIsActive = true;
};
}