#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>
#include <string>

namespace SSE {
using EntityId = std::uint32_t;

struct Component {
    EntityId owner = 0;
    std::string typeName;

    virtual ~Component() = default;
};
}  // namespace SSE

#endif  // COMPONENT_H
