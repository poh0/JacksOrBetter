#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

namespace UI {
class PushButton {
public:

    PushButton(const sf::Texture& idleTexture, const sf::Texture& clickedTexture);

    void draw(sf::RenderWindow& renderWindow);

    bool contains(sf::Vector2f point) const;

    void setText(const std::string& text);
    void setPosition(sf::Vector2f pos);

    void onPress();
    void onRelease();

private:

    sf::Text mText;
    bool mHasText = false;

    const sf::Texture& mIdleTexture;
    const sf::Texture& mClickedTexture;

    sf::Sprite mSprite;

    bool mIsPressed = false;
    std::function<void()> mCallback;
};
}