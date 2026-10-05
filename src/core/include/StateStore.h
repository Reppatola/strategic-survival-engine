#ifndef STATE_STORE_H
#define STATE_STORE_H

#include <mutex>
#include <string>

namespace SSE {

struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

// ============================================================
// КОНТРАКТ: StateStore
// Единое хранилище глобального состояния.
// Все методы потокобезопасны (защищены mutex).
// ============================================================
class StateStore {
   public:
    static StateStore& getInstance();

    StateStore(const StateStore&) = delete;
    StateStore& operator=(const StateStore&) = delete;

    // --- AlertLevel ---
    // Издатель (запись): AlertSystem
    // Читатели: ZombieAISystem, HUDSystem
    void setAlertLevel(float value);
    [[nodiscard]] float getAlertLevel() const;

    // --- GlobalNoiseLevel ---
    // Издатель: NoiseSystem
    // Читатели: ZombieAISystem
    void setGlobalNoiseLevel(float value);
    [[nodiscard]] float getGlobalNoiseLevel() const;

    // --- LastKnownPosition ---
    // Издатель: PerceptionSystem
    // Читатели: ZombieAISystem
    void setLastKnownPosition(const Vec3& pos);
    [[nodiscard]] Vec3 getLastKnownPosition() const;

   private:
    StateStore() = default;

    mutable std::mutex mutex;

    float alertLevel = 0.0f;
    float globalNoiseLevel = 0.0f;
    Vec3 lastKnownPosition{};
};

}  // namespace SSE

#endif  // STATE_STORE_H