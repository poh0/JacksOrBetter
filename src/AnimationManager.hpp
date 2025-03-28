#pragma once

#include <vector>
#include <memory>
#include "Animation.hpp"

class AnimationManager {
public:
    void addAnimation(std::unique_ptr<Animation> animation);
    void update(float deltaTime);

private:
    std::vector<std::unique_ptr<Animation>> mAnimations;
};