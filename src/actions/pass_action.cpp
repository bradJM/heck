#include "pass_action.h"
#include "../actor.h"
#include "../map.h"

namespace nsd {
PassAction::PassAction(Actor *owner) : Action(owner) {}

ActionResult PassAction::perform([[maybe_unused]] Map &map) {
  getOwner()->spendEnergy(100);

  return {true, nullptr};
}
} // namespace nsd
