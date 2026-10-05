#pragma once
#include <string>
#include <unordered_map>

// ============================================================
// КОНТРАКТ 2: StateStore
// Глобальное состояние. Только системы с явным правом
// записи могут изменять значения.
// ============================================================

namespace SSE {

class StateStore {
public:
    // Только чтение — для большинства систем
    [[nodiscard]] float getAlertLevel() const;
    [[nodiscard]] float getGlobalNoiseLevel() const;

    // Запись — только для уполномоченных систем
    void setAlertLevel(float value);        // Вызывает: AlertSystem
    void setGlobalNoiseLevel(float value);  // Вызывает: NoiseSystem

private:
    float alertLevel_ = 0.0f;
    float globalNoiseLevel_ = 0.0f;
};

} // namespace SSE