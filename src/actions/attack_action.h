#ifndef HECK_ATTACK_ACTION_H
#define HECK_ATTACK_ACTION_H

#include "action.h"
#include <glm/vec2.hpp>

namespace nsd {
class AttackAction : public Action {
public:
  explicit AttackAction(const glm::ivec2 &targetPosition);

  ActionResult perform(Actor &actor, ActorCollection &actors, Map &map) override;

private:
  glm::ivec2 targetPosition_;
};
} // namespace nsd

#endif // HECK_ATTACK_ACTION_H
