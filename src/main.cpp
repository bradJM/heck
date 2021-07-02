#include "game.h"
#include <SDL2/SDL.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  auto game{nsd::Game{}};
  game.loop();

  return 0;
}
