#include "AnimationManager.hpp"

void AnimationManager::addAnimation(std::unique_ptr<Animation> animation)
{
    mAnimations.push_back(std::move(animation));
}

void AnimationManager::update(float deltaTime)
{
    for (auto& anim : mAnimations) {
        anim->update(deltaTime);
    }

    // Remove animations that are finished
    // Erase-remove idiom (C++11+)
    mAnimations.erase(std::remove_if(mAnimations.begin(), mAnimations.end(),
        [](const std::unique_ptr<Animation>& anim) {
            return anim->isFinished();
        }), 
        mAnimations.end()
    );
}
