#pragma once

#include "IAnimBehavior.hpp"

class RotationBehavior : public IAnimBehavior {
public:
    RotationBehavior(const sf::Vector3f& start, const sf::Vector3f& end);
    void update(sw::Sprite3d& target, float elapsedTime, float duration);
private:
    static sf::Vector3f lerp3d(const sf::Vector3f& start, const sf::Vector3f& end, float t);
    sf::Vector3f mStartAngles;
    sf::Vector3f mEndAngles;
};