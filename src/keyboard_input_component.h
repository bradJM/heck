#ifndef HECK_KEYBOARD_MOVEMENT_COMPONENT_H
#define HECK_KEYBOARD_MOVEMENT_COMPONENT_H

#include "component.h"

namespace nsd {
class Keyboard;

class KeyboardInputComponent : public Component {
public:
  KeyboardInputComponent(Actor &owner, Keyboard &keyboard);

  void update(float deltaTime) override;

private:
  Keyboard &keyboard_;
};
} // namespace nsd

#endif
