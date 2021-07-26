#ifndef HECK_AI_COMPONENT_H
#define HECK_AI_COMPONENT_H

#include "component.h"
#include <memory>

namespace nsd {
class Action;

class AiComponent : public Component {
public:
  std::unique_ptr<Action> produceAction() override;
};
} // namespace nsd

#endif
