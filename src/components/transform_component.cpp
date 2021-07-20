#include "transform_component.h"
#include "../actor.h"

namespace nsd {
TransformComponent::TransformComponent(Actor *owner, const glm::ivec2 &position,
                                       bool blocksMovement)
    : Component(owner), position_(position), blocksMovement_(blocksMovement) {}
} // namespace nsd
