#include "sprite_component.h"
#include "../actor.h"
#include "../graphics.h"
#include "transform_component.h"

namespace nsd {
SpriteComponent::SpriteComponent(Actor *owner, Atlas *atlas, int spriteIndex,
                                 const glm::u8vec4 &color)
    : Component(owner), atlas_(atlas), spriteIndex_(spriteIndex), color_(color) {}

void SpriteComponent::render(Graphics &graphics) {
  const auto transform{getOwner()->getComponent<TransformComponent>()};
  const auto &position{transform->getPosition()};
  const auto sourceRect{atlas_->getSourceRectangle(spriteIndex_)};
  const auto destRect{atlas_->getDestinationRectangle(position)};

  graphics.blit(atlas_->getTexture(), sourceRect, destRect, color_);
}
} // namespace nsd
