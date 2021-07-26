#include "move_action.h"
#include "../actor.h"
#include "../game.h"
#include "../map.h"

namespace nsd {
MoveAction::MoveAction(const glm::ivec2 &direction) : direction_(direction) {}

ActionResult MoveAction::perform(Actor &actor, ActorCollection &actors, Map &map) {
  actor.move(direction_);

  if (!map.isWalkable(actor.getPosition())) {
    actor.move(-direction_);

    return {false, nullptr};
  }

  if (actors.checkAny([&actor](const auto &other) { return other.blocks(actor); })) {
    // replace this with an attack action
    actor.move(-direction_);

    return {false, nullptr};
  }

  actor.spendEnergy(100);
  map.onActorMoved(actor);

  return {true, nullptr};
}
} // namespace nsd
