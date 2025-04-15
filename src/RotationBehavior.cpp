#include "RotationBehavior.hpp"

RotationBehavior::RotationBehavior(const sf::Vector3f &startAngles, const sf::Vector3f &endAngles): mStartAngles(startAngles), mEndAngles(endAngles)
{
}

void RotationBehavior::update(sw::Sprite3d &target, float elapsedTime, float duration)
{
    float t = std::min(elapsedTime / duration, 1.0f); // Normalize time between 0 and 1
    target.setRotation3d(lerp3d(mStartAngles, mEndAngles, t));
}

sf::Vector3f RotationBehavior::lerp3d(const sf::Vector3f &start, const sf::Vector3f &end, float t)
{
    return start + t * (end - start);
}
