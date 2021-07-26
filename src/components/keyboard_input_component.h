#ifndef HECK_KEYBOARD_INPUT_COMPONENT_H
#define HECK_KEYBOARD_INPUT_COMPONENT_H

#include "component.h"
#include <memory>

namespace nsd {
class Action;

class KeyboardInputComponent : public Component {
public:
  std::unique_ptr<Action> produceAction() override;
};
} // namespace nsd

#endif
