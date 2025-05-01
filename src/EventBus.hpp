#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

enum class GameEvent {
    DealAnimComplete,
    BetChanged,
    CreditsChanged,
    DealingCards,
    HandEndedLoss
};

class EventBus {
public:
    using Handler = std::function<void()>;

    void subscribe(GameEvent event, Handler handler) {
        mHandlers[event].push_back(handler);
    }

    void emit(GameEvent event) {
        auto it = mHandlers.find(event);
        if (it != mHandlers.end()) {
            for (const auto& handler : it->second) {
                handler();
            }
        }
    }

private:
    std::unordered_map<GameEvent, std::vector<Handler>> mHandlers;
};