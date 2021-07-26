#ifndef HECK_SPRITE_COMPONENT_H
#define HECK_SPRITE_COMPONENT_H

#include "component.h"
#include <glm/vec4.hpp>

namespace nsd {
class Actor;

class Atlas;

class SpriteComponent : public Component {
public:
  SpriteComponent(int spriteIndex, const glm::u8vec4 &color);

  void render(const Actor &owner, Graphics &graphics) override;

private:
  int spriteIndex_;

  glm::u8vec4 color_;
};
} // namespace nsd

#endif
