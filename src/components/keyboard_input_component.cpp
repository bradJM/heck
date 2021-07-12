#include "keyboard_input_component.h"
#include "../actions/move_action.h"
#include "../keyboard.h"
#include <glm/vec2.hpp>

namespace nsd {
KeyboardInputComponent::KeyboardInputComponent(Actor *owner, Keyboard *keyboard)
    : Component(owner), keyboard_(keyboard) {}

std::unique_ptr<Action> KeyboardInputComponent::produceAction() {
  auto direction{glm::ivec2{0}};

  if (keyboard_->isKeyPressed(Keyboard::Key::Up)) {
    direction.y -= 1;
  }

  if (keyboard_->isKeyPressed(Keyboard::Key::Down)) {
    direction.y += 1;
  }

  if (keyboard_->isKeyPressed(Keyboard::Key::Left)) {
    direction.x -= 1;
  }

  if (keyboard_->isKeyPressed(Keyboard::Key::Right)) {
    direction.x += 1;
  }

  if (direction != glm::ivec2{0}) {
    return std::make_unique<MoveAction>(getOwner(), direction);
  }

  return nullptr;
}
} // namespace nsd
