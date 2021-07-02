#ifndef HECK_KEYBOARD_H
#define HECK_KEYBOARD_H

#include "bitmask.h"

struct SDL_KeyboardEvent;

namespace nsd {
class Keyboard {
public:
  enum class Key { None, Up, Down, Left, Right };

  void onKeyDown(const SDL_KeyboardEvent &event);

  void onKeyUp(const SDL_KeyboardEvent &event);

  bool isKeyPressed(Key key) const;

private:
  Bitmask pressedKeys_;
};
} // namespace nsd

#endif
