#include "move_action.h"
#include "../actor.h"
#include "../components/transform_component.h"
#include "../map.h"

namespace nsd {
MoveAction::MoveAction(Actor *owner, const glm::ivec2 &direction)
    : Action(owner), direction_(direction) {}

ActionResult MoveAction::perform(Map &map) {
  const auto transform{getOwner()->getComponent<TransformComponent>()};
  const auto &position{transform->getPosition()};
  const auto newPosition{glm::ivec2{position.x + direction_.x, position.y + direction_.y}};

  if (!map.isWalkable(newPosition)) {
    return {false, nullptr};
  }

  transform->setPosition(newPosition);
  map.computeFov(newPosition, 8);

  getOwner()->spendEnergy(100);

  return {true, nullptr};
}
} // namespace nsd
