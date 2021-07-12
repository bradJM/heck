#ifndef HECK_KEYBOARD_INPUT_COMPONENT_H
#define HECK_KEYBOARD_INPUT_COMPONENT_H

#include "component.h"
#include <memory>

namespace nsd {
class Keyboard;

class Action;

class Actor;

class KeyboardInputComponent : public Component {
public:
  KeyboardInputComponent(Actor *owner, Keyboard *keyboard);

  std::unique_ptr<Action> produceAction() override;

private:
  Keyboard *keyboard_;
};
} // namespace nsd

#endif
