#include "MoveBehavior.hpp"

MoveBehavior::MoveBehavior(const sf::Vector2f &start, const sf::Vector2f &end) : mStart(start), mEnd(end)
{
}

void MoveBehavior::update(sw::Sprite3d &target, float elapsedTime, float duration)
{
    float t = std::min(elapsedTime / duration, 1.0f); // Normalize time between 0 and 1
    target.setPosition(lerp(mStart, mEnd, t));
}

sf::Vector2f MoveBehavior::lerp(const sf::Vector2f &start, const sf::Vector2f &end, float t)
{
    return start + t * (end - start);
}