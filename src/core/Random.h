#ifndef SSE_CORE_RANDOM_H
#define SSE_CORE_RANDOM_H

#include <cstdint>
#include <random>

namespace SSE {

// ============================================================
// RANDOM — единый генератор случайных чисел.
// Используется для выбора вариантов: цвета, формы, размера.
// Детерминирован — с одним seed мир воспроизводим.
// ============================================================
class Random {
   public:
    explicit Random(std::uint32_t seed = 42) : gen_(seed) {}

    // Целое в диапазоне [min, max]
    std::int32_t intRange(std::int32_t min, std::int32_t max) {
        std::uniform_int_distribution<std::int32_t> d(min, max);
        return d(gen_);
    }

    // Дробное в диапазоне [min, max]
    float floatRange(float min, float max) {
        std::uniform_real_distribution<float> d(min, max);
        return d(gen_);
    }

    // Случайный элемент массива
    template <typename T, std::size_t N>
    const T& pick(const T (&arr)[N]) {
        return arr[intRange(0, static_cast<std::int32_t>(N) - 1)];
    }

   private:
    std::mt19937 gen_;
};

}  // namespace SSE

#endif  // SSE_CORE_RANDOM_H