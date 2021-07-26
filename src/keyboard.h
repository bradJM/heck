#ifndef HECK_KEYBOARD_H
#define HECK_KEYBOARD_H

#include "bitmask.h"
#include "singleton.h"

struct SDL_KeyboardEvent;

namespace nsd {
class Keyboard : public Singleton<Keyboard> {
public:
  enum class Key { None, Up, Down, Left, Right, Period };

  void onKeyDown(const SDL_KeyboardEvent &event);

  void onKeyUp(const SDL_KeyboardEvent &event);

  bool isKeyPressed(Key key) const;

private:
  Bitmask pressedKeys_;
};
} // namespace nsd

#endif
