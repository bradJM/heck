#ifndef HECK_MOVE_ACTION_H
#define HECK_MOVE_ACTION_H

#include "action.h"
#include <glm/vec2.hpp>

namespace nsd {
class MoveAction : public Action {
public:
  explicit MoveAction(const glm::ivec2 &direction);

  ActionResult perform(Actor &actor, ActorCollection &actors, Map &map) override;

private:
  glm::ivec2 direction_;
};
} // namespace nsd

#endif
