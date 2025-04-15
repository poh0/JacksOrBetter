#pragma once
#include <SelbaWard/Sprite3d.hpp>

class IAnimBehavior {
public:
    virtual ~IAnimBehavior() = default;
    virtual void update(sw::Sprite3d& target, float elapsedTime, float duration) = 0;
};