#include "actor.h"
#include "actions/action.h"
#include "components/component.h"
#include "graphics.h"

namespace nsd {
Actor::Actor(int speed, int startingEnergy) : speed_(speed), energy_(startingEnergy) {}

bool Actor::refresh() {
  energy_ += speed_;

  return energy_ >= 100;
}

void Actor::spendEnergy(int amount) { energy_ -= amount; }

std::unique_ptr<Action> Actor::turn() {
  for (const auto &component : components_) {
    // Just return the first available action for now. Maybe look into a priority system later.
    if (auto action{component->produceAction()}; action != nullptr) {
      return action;
    }
  }

  return nullptr;
}

void Actor::render(Graphics &graphics) const {
  for (const auto &component : components_) {
    component->render(graphics);
  }
}
} // namespace nsd
