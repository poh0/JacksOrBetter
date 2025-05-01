#include "PushButton.hpp"
#include "Config.hpp"

UI::PushButton::PushButton(const sf::Texture &idleTexture, const sf::Texture &clickedTexture, float shift_y)
    : mIdleTexture(idleTexture),
      mClickedTexture(clickedTexture),
      mSprite(sf::Sprite(idleTexture)),
      mText(sf::Text(ResourceManager::getInstance().getFont("toxi"))),
      mShiftY(shift_y)
{
}

void UI::PushButton::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(mSprite);
    if (mHasText) renderWindow.draw(mText);
}

bool UI::PushButton::contains(sf::Vector2f point) const
{
    return mSprite.getGlobalBounds().contains(point);
}

void UI::PushButton::setCallback(std::function<void()> callback)
{
    mCallback = callback;
}

void UI::PushButton::setText(const std::string &text, unsigned int size)
{
    mHasText = true;
    mText.setFillColor(sf::Color::Black);
    mText.setString(text);
    mText.setCharacterSize(size);
    mText.setPosition(mSprite.getGlobalBounds().getCenter());
    mText.setOrigin(mText.getLocalBounds().getCenter() + sf::Vector2f{0, mShiftY});

}

void UI::PushButton::setPosition(sf::Vector2f pos)
{
    mSprite.setPosition(pos);
    mText.setPosition(mSprite.getGlobalBounds().getCenter());
}

void UI::PushButton::onPress()
{
    if (mIsPressed || !mIsActive) return;
    mIsPressed = true;
    mSprite.setTexture(mClickedTexture);
    setPosition(mSprite.getPosition() + sf::Vector2f{0.0f, mShiftY});
}

void UI::PushButton::onRelease(sf::Vector2f mousePos)
{
    if (!mIsPressed || !mIsActive) return;
    mIsPressed = false;
    mSprite.setTexture(mIdleTexture);
    setPosition(mSprite.getPosition() + sf::Vector2f{0.0f, -mShiftY});

    // If mouse is not on button when releasing, cancel action.
    if (this->contains(mousePos) && mCallback) {
        mCallback();
    }
}

void UI::PushButton::setActive(bool active)
{
    if (mIsActive == active) return;
    mIsActive = active;

    sf::Color color = mSprite.getColor();
    if (mIsActive) {
        color.a = 255;
    } else {
        color.a = 125;
    }
    mSprite.setColor(color);
}