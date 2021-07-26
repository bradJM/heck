#include "ai_component.h"
#include "../actions/action.h"
#include "../actions/wait_action.h"
#include "../game.h"

namespace nsd {
std::unique_ptr<Action> AiComponent::produceAction() { return std::make_unique<WaitAction>(); }
} // namespace nsd
