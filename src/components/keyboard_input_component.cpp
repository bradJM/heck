#include "keyboard_input_component.h"
#include "../actions/action.h"
#include "../actions/move_action.h"
#include "../actions/wait_action.h"
#include "../game.h"
#include "../keyboard.h"
#include <glm/vec2.hpp>

namespace nsd {
std::unique_ptr<Action> KeyboardInputComponent::produceAction() {
  const auto &keyboard{Keyboard::getInstance()};

  if (keyboard.isKeyPressed(Keyboard::Key::Period)) {
    return std::make_unique<WaitAction>();
  }

  auto direction{glm::ivec2{0}};

  if (keyboard.isKeyPressed(Keyboard::Key::Up)) {
    direction.y -= 1;
  }

  if (keyboard.isKeyPressed(Keyboard::Key::Down)) {
    direction.y += 1;
  }

  if (keyboard.isKeyPressed(Keyboard::Key::Left)) {
    direction.x -= 1;
  }

  if (keyboard.isKeyPressed(Keyboard::Key::Right)) {
    direction.x += 1;
  }

  if (direction != glm::ivec2{0}) {
    return std::make_unique<MoveAction>(direction);
  }

  return nullptr;
}
} // namespace nsd
