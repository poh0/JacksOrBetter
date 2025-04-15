#include "Animation.hpp"

Animation::Animation(sw::Sprite3d &target, sf::Vector2f start, sf::Vector2f end, float delay, float duration, Callback callback)
    : mTarget(target), mStart(start), mEnd(end), mDelay(delay), mDuration(duration), mCallback(callback), mFinished(false)
{
        // mTarget.setPosition(mStart);
        mHasDelay = static_cast<bool>(delay);
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
    
    float t = std::min(mElapsedTime / mDuration, 1.0f); // Normalize time between 0 and 1
    
    mTarget.setPosition(lerp(mStart, mEnd, t));

    if (t >= 1.0f) {
        mFinished = true;
        if (mCallback) mCallback(); // Call the callback when animation is done
    }
}

void Animation::setCallback(Callback cb)
{
    mCallback = cb;
}

sf::Vector2f Animation::lerp(const sf::Vector2f &start, const sf::Vector2f &end, float t)
{
    return start + t * (end - start);
}