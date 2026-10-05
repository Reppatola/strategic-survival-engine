#pragma once
#include <cstdint>
#include <string>

// ============================================================
// КОНТРАКТ 3: Component
// Базовый интерфейс для всех компонентов данных.
// Данные НЕ ЗНАЮТ, как они используются.
// ============================================================

namespace SSE {

using EntityId = std::uint32_t;

struct Component {
    EntityId owner = 0;
    std::string typeName;

    virtual ~Component() = default;
};

} // namespace SSE