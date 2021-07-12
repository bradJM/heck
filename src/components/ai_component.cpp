#include "ai_component.h"
#include "../actions/pass_action.h"
#include "../actor.h"

namespace nsd {
AiComponent::AiComponent(Actor *owner) : Component(owner) {}

std::unique_ptr<Action> AiComponent::produceAction() {
  return std::make_unique<PassAction>(getOwner());
}
} // namespace nsd
