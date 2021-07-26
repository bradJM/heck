#ifndef HECK_WAIT_ACTION_H
#define HECK_WAIT_ACTION_H

#include "action.h"

namespace nsd {
class WaitAction : public Action {
public:
  ActionResult perform(Actor &actor, ActorCollection &actors, Map &map) override;
};
} // namespace nsd

#endif
