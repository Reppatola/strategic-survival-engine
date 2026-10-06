#pragma once
#include <cstdint>

namespace SSE::Render {

void buildFadeMask();
std::uint8_t fadeAt(int x, int y);
const std::uint8_t* fadeData();

} // namespace SSE::Render
