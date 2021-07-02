#include "sprite_component.h"
#include "actor.h"

namespace nsd {
SpriteComponent::SpriteComponent(Actor &owner, const std::string &texturePath, Graphics &graphics,
                                 int spriteId, int width, int height, const glm::u8vec4 &color)
    : Component(owner), spriteId_(spriteId), color_(color),
      atlas_(texturePath, graphics, width, height) {}

void SpriteComponent::render(Graphics &graphics) {
  const auto position{getOwner().getPosition()};
  const auto sourceRect{atlas_.getSourceRectangle(spriteId_)};
  const auto destRect{atlas_.getDestinationRectangle(position)};

  graphics.blit(atlas_.getTexture(), sourceRect, destRect, color_);
}
} // namespace nsd
