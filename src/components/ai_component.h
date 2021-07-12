#ifndef HECK_AI_COMPONENT_H
#define HECK_AI_COMPONENT_H

#include "component.h"
#include <memory>

namespace nsd {
class Action;

class Actor;

class AiComponent : public Component {
public:
  explicit AiComponent(Actor *owner);

  std::unique_ptr<Action> produceAction() override;
};
} // namespace nsd

#endif
