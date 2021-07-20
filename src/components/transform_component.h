#ifndef HECK_TRANSFORM_COMPONENT_H
#define HECK_TRANSFORM_COMPONENT_H

#include "component.h"
#include <glm/vec2.hpp>

namespace nsd {
class Actor;

class TransformComponent : public Component {
public:
  TransformComponent(Actor *owner, const glm::ivec2 &position, bool blocksMovement);

  const glm::ivec2 &getPosition() const { return position_; }

  void setPosition(const glm::ivec2 &position) { position_ = position; }

  bool blocksMovement() const { return blocksMovement_; }

private:
  glm::ivec2 position_;

  bool blocksMovement_;
};
} // namespace nsd

#endif
