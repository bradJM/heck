#include "transform_component.h"
#include "../actor.h"

namespace nsd {
TransformComponent::TransformComponent(Actor *owner, const glm::ivec2 &position)
    : Component(owner), position_(position) {}
} // namespace nsd
