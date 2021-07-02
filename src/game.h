#ifndef HECK_GAME_H
#define HECK_GAME_H

#include "actor.h"
#include "keyboard.h"
#include <SDL2/SDL2_framerate.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace nsd {
class Graphics;

class Tileset;

class Game {
public:
  Game();

  Game(const Game &) = delete;

  Game(Game &&) = delete;

  ~Game();

  Game &operator=(const Game &) = delete;

  Game &operator=(Game &&) = delete;

  void loop();

  void processInput();

  void update();

  void render();

private:
  FPSmanager fpsManager_{};

  std::unique_ptr<Graphics> graphics_{nullptr};

  std::unique_ptr<Tileset> tileset_{nullptr};

  std::uint32_t ticks_{0};

  bool isRunning_{true};

  Keyboard keyboard_{};

  std::vector<Actor> actors_{};
};
} // namespace nsd

#endif
