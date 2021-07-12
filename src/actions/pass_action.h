#ifndef HECK_PASS_ACTION_H
#define HECK_PASS_ACTION_H

#include "action.h"

namespace nsd {
class PassAction : public Action {
public:
  explicit PassAction(Actor *owner);

  ActionResult perform() override;
};
} // namespace nsd

#endif
