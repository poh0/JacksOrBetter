#pragma once

#include "IAnimBehavior.hpp"
#include <SelbaWard/Sprite3d.hpp>

class MoveBehavior : public IAnimBehavior {
public:
    MoveBehavior(const sf::Vector2f& start, const sf::Vector2f& end);
    void update(sw::Sprite3d& target, float elapsedTime, float duration) override;

private:
    sf::Vector2f mStart, mEnd;
    static sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);
};