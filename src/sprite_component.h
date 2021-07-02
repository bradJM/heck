#ifndef HECK_SPRITE_COMPONENT_H
#define HECK_SPRITE_COMPONENT_H

#include "component.h"
#include "graphics.h"
#include <glm/vec4.hpp>
#include <string>

namespace nsd {
class Actor;

class SpriteComponent : public Component {
public:
  SpriteComponent(Actor &owner, const std::string &texturePath, Graphics &graphics, int spriteId,
                  int width, int height, const glm::u8vec4 &color = glm::u8vec4{0xFF});

  void render(Graphics &graphics) override;

private:
  int spriteId_;

  glm::u8vec4 color_;

  Atlas atlas_;
};
} // namespace nsd

#endif
