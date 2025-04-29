#include "PushButton.hpp"
#include "Config.hpp"

UI::PushButton::PushButton(const sf::Texture &idleTexture, const sf::Texture &clickedTexture)
    : mIdleTexture(idleTexture),
      mClickedTexture(clickedTexture),
      mSprite(sf::Sprite(idleTexture)),
      mText(sf::Text(ResourceManager::getInstance().getFont("toxi")))
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

void UI::PushButton::setText(const std::string &text)
{
    mHasText = true;
    mText.setString(text);
    mText.setPosition(mSprite.getGlobalBounds().getCenter());
    mText.setOrigin(mText.getLocalBounds().getCenter() + sf::Vector2f{0, 5.0f});
}

void UI::PushButton::setPosition(sf::Vector2f pos)
{
    mSprite.setPosition(pos);
    mText.setPosition(mSprite.getGlobalBounds().getCenter());
}

void UI::PushButton::onPress()
{
    if (mIsPressed) return;
    mIsPressed = true;
    mSprite.setTexture(mClickedTexture);
    setPosition(mSprite.getPosition() + sf::Vector2f{0.0f, Config::DEALBTN_ANIM_Y_OFFSET});
}

void UI::PushButton::onRelease()
{
    if (!mIsPressed) return;
    mIsPressed = false;
    mSprite.setTexture(mIdleTexture);
    setPosition(mSprite.getPosition() + sf::Vector2f{0.0f, -Config::DEALBTN_ANIM_Y_OFFSET});
}
