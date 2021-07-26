#include "attack_action.h"

namespace nsd {
AttackAction::AttackAction(const glm::ivec2 &targetPosition) : targetPosition_(targetPosition) {}

ActionResult AttackAction::perform([[maybe_unused]] Actor &actor,
                                   [[maybe_unused]] ActorCollection &actors,
                                   [[maybe_unused]] Map &map) {
  return {true, nullptr};
}
} // namespace nsd
