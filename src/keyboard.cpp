#include "keyboard.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>

namespace nsd {
void Keyboard::onKeyDown(const SDL_KeyboardEvent &event) {
  if (event.repeat != 0) {
    return;
  }

  switch (event.keysym.scancode) {
  case SDL_SCANCODE_UP:
  case SDL_SCANCODE_W:
    pressedKeys_.setBit(static_cast<int>(Key::Up));
    break;

  case SDL_SCANCODE_DOWN:
  case SDL_SCANCODE_S:
    pressedKeys_.setBit(static_cast<int>(Key::Down));
    break;

  case SDL_SCANCODE_LEFT:
  case SDL_SCANCODE_A:
    pressedKeys_.setBit(static_cast<int>(Key::Left));
    break;

  case SDL_SCANCODE_RIGHT:
  case SDL_SCANCODE_D:
    pressedKeys_.setBit(static_cast<int>(Key::Right));
    break;

  default:
    break;
  }
}

void Keyboard::onKeyUp(const SDL_KeyboardEvent &event) {
  if (event.repeat != 0) {
    return;
  }

  switch (event.keysym.scancode) {
  case SDL_SCANCODE_UP:
  case SDL_SCANCODE_W:
    pressedKeys_.clearBit(static_cast<int>(Key::Up));
    break;

  case SDL_SCANCODE_DOWN:
  case SDL_SCANCODE_S:
    pressedKeys_.clearBit(static_cast<int>(Key::Down));
    break;

  case SDL_SCANCODE_LEFT:
  case SDL_SCANCODE_A:
    pressedKeys_.clearBit(static_cast<int>(Key::Left));
    break;

  case SDL_SCANCODE_RIGHT:
  case SDL_SCANCODE_D:
    pressedKeys_.clearBit(static_cast<int>(Key::Right));
    break;

  default:
    break;
  }
}

bool Keyboard::isKeyPressed(Key key) const { return pressedKeys_.getBit(static_cast<int>(key)); }
} // namespace nsd
