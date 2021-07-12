#ifndef HECK_SPRITE_COMPONENT_H
#define HECK_SPRITE_COMPONENT_H

#include "component.h"
#include <glm/vec4.hpp>

namespace nsd {
class Atlas;

class SpriteComponent : public Component {
public:
  SpriteComponent(Actor *owner, Atlas *atlas, int spriteIndex, const glm::u8vec4 &color);

  void render(Graphics &graphics) override;

private:
  Atlas *atlas_;

  int spriteIndex_;

  glm::u8vec4 color_;
};
} // namespace nsd

#endif
