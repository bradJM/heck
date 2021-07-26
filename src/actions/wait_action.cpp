#include "../actor.h"
#include "../map.h"
#include "wait_action.h"

namespace nsd {
ActionResult WaitAction::perform(Actor &actor, [[maybe_unused]] ActorCollection &actors,
                                 [[maybe_unused]] Map &map) {
  actor.spendEnergy(100);

  return {true, nullptr};
}
} // namespace nsd
