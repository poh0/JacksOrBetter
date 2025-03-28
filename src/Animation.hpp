#pragma once
#include <SFML/Graphics.hpp>
#include <SelbaWard/Sprite3d.hpp>
#include <functional>

class Animation {
public:
    using Callback = std::function<void()>; // Function called when animation ends

    Animation(sw::Sprite3d& target, sf::Vector2f start, sf::Vector2f end, float delay, float duration, Callback callback = nullptr);

    void update(float deltaTime);

    bool isFinished() const { return mFinished; }

    void setCallback(Callback cb);

private:
    sw::Sprite3d& mTarget;
    sf::Vector2f mStart, mEnd;
    float mDuration;
    float mDelay;  // Delay in seconds before the animation is fired after it's creation
    float mElapsedTime = 0.0f;
    bool mHasDelay;
    bool mFinished;
    Callback mCallback;

    static sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);
};