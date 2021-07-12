#include "pass_action.h"
#include "../actor.h"

namespace nsd {
PassAction::PassAction(Actor *owner) : Action(owner) {}

ActionResult PassAction::perform() {
  getOwner()->spendEnergy(100);

  return {true, nullptr};
}
} // namespace nsd
