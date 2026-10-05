#include "EventBus.h"

#include <algorithm>

SubscriptionId EventBus::subscribe(const std::string& eventType, Callback callback) {
    std::lock_guard<std::mutex> lock(mutex);
    SubscriptionId id = nextId++;
    subscribers[eventType].push_back({id, std::move(callback)});
    return id;
}

void EventBus::unsubscribe(const std::string& eventType, SubscriptionId id) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = subscribers.find(eventType);
    if (it == subscribers.end()) return;

    auto& list = it->second;
    list.erase(
        std::remove_if(list.begin(), list.end(), [id](const Subscriber& s) { return s.id == id; }),
        list.end());

    if (list.empty()) {
        subscribers.erase(it);
    }
}

void EventBus::publish(const std::string& eventType, const std::string& payload) const {
    std::vector<Callback> callbacksCopy;

    {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = subscribers.find(eventType);
        if (it == subscribers.end()) return;

        // Копируем колбэки, чтобы не держать mutex во время их вызова.
        // Это защищает от дедлока, если колбэк сам вызовет subscribe/publish.
        callbacksCopy.reserve(it->second.size());
        for (const auto& sub : it->second) {
            callbacksCopy.push_back(sub.callback);
        }
    }

    for (const auto& cb : callbacksCopy) {
        cb(payload);
    }
}