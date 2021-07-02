// Credit: https://thatgamesguy.co.uk/cpp-game-dev-7/
#include "actor.h"
#include "graphics.h"

namespace nsd {
Actor::Actor(const glm::ivec2 &position) : position_(position) {}

void Actor::update(float deltaTime) {
  for (auto iter = components_.rbegin(); iter != components_.rend(); ++iter) {
    (*iter)->update(deltaTime);
  }
}

void Actor::render(Graphics &graphics) const {
  for (auto iter = components_.rbegin(); iter != components_.rend(); ++iter) {
    (*iter)->render(graphics);
  }
}
} // namespace nsd
