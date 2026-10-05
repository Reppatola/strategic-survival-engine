#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

using Callback = std::function<void(const std::string&)>;
using SubscriptionId = std::uint64_t;

class EventBus {
   public:
    static EventBus& getInstance() {
        static EventBus instance;
        return instance;
    }

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    // Возвращает ID подписки для последующей отписки
    SubscriptionId subscribe(const std::string& eventType, Callback callback);

    // Отписка по ID — надёжнее, чем сравнение std::function
    void unsubscribe(const std::string& eventType, SubscriptionId id);

    void publish(const std::string& eventType, const std::string& payload) const;

   private:
    EventBus() = default;

    struct Subscriber {
        SubscriptionId id;
        Callback callback;
    };

    std::map<std::string, std::vector<Subscriber>> subscribers;
    SubscriptionId nextId = 1;
    mutable std::mutex mutex;
};

#endif  // EVENT_BUS_H