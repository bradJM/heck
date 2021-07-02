#include "keyboard_input_component.h"
#include "actor.h"
#include "keyboard.h"

namespace nsd {
KeyboardInputComponent::KeyboardInputComponent(Actor &owner, Keyboard &keyboard)
    : Component(owner), keyboard_(keyboard) {}

void KeyboardInputComponent::update([[maybe_unused]] float deltaTime) {
  auto &owner{getOwner()};
  auto position{glm::ivec2{owner.getPosition()}};

  if (keyboard_.isKeyPressed(Keyboard::Key::Up)) {
    position.y -= 1;
  }

  if (keyboard_.isKeyPressed(Keyboard::Key::Down)) {
    position.y += 1;
  }

  if (keyboard_.isKeyPressed(Keyboard::Key::Left)) {
    position.x -= 1;
  }

  if (keyboard_.isKeyPressed(Keyboard::Key::Right)) {
    position.x += 1;
  }

  owner.setPosition(position);
}
} // namespace nsd
