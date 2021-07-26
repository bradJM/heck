#include "actor.h"
#include "actions/action.h"
#include "components/component.h"
#include "game.h"
#include "graphics.h"

namespace nsd {
Actor::Actor(const glm::ivec2 &position, int speed, int startingEnergy, bool blocksMovement)
    : id_(++nextId_), position_(position), speed_(speed), energy_(startingEnergy),
      blocksMovement_(blocksMovement) {}

void Actor::move(const glm::ivec2 &direction) {
  position_.x += direction.x;
  position_.y += direction.y;
}

bool Actor::blocks(const Actor &other) const {
  if (other == *this) {
    return false;
  }

  return blocksMovement_ && position_ == other.getPosition();
}

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
    component->render(*this, graphics);
  }
}
} // namespace nsd
