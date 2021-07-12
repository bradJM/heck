#include "move_action.h"
#include "../actor.h"
#include "../components/transform_component.h"

namespace nsd {
MoveAction::MoveAction(Actor *owner, const glm::ivec2 &direction)
    : Action(owner), direction_(direction) {}

ActionResult MoveAction::perform() {
  const auto transform{getOwner()->getComponent<TransformComponent>()};
  const auto &position{transform->getPosition()};
  const auto newPosition{glm::ivec2{position.x + direction_.x, position.y + direction_.y}};

  transform->setPosition(newPosition);

  getOwner()->spendEnergy(100);

  return {true, nullptr};
}
} // namespace nsd
