#include "Animation.hpp"

Animation::Animation(sw::Sprite3d &target, std::unique_ptr<IAnimBehavior> behavior, float delay, float duration, Callback callback)
    : mTarget(target), mBehavior(std::move(behavior)), mDelay(delay), mHasDelay(delay > 0.0f), mDuration(duration), mCallback(callback), mFinished(false)
{
}

void Animation::update(float deltaTime)
{
    if (mFinished) return;
        
    mElapsedTime += deltaTime;

    if (mHasDelay) {
        if (mElapsedTime < mDelay) {
            return;
        }
        mElapsedTime = mElapsedTime - mDelay;
        mHasDelay = false;
    }
    
    mBehavior->update(mTarget, mElapsedTime, mDuration);

    //float t = std::min(mElapsedTime / mDuration, 1.0f); // Normalize time between 0 and 1
    // mTarget.setPosition(lerp(mStart, mEnd, t));

    if ((mDuration - mElapsedTime <= 0)) {
        mFinished = true;
        if (mCallback) mCallback(); // Call the callback when animation is done
    }
}

void Animation::setCallback(Callback cb)
{
    mCallback = cb;
}

// sf::Vector2f Animation::lerp(const sf::Vector2f &start, const sf::Vector2f &end, float t)
// {
//     return start + t * (end - start);
// }