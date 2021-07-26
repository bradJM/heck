#include "sprite_component.h"
#include "../actor.h"
#include "../graphics.h"

namespace nsd {
SpriteComponent::SpriteComponent(int spriteIndex, const glm::u8vec4 &color)
    : spriteIndex_(spriteIndex), color_(color) {}

void SpriteComponent::render(const Actor &owner, Graphics &graphics) {
  graphics.blitSprite(spriteIndex_, owner.getPosition(), color_);
}
} // namespace nsd
