#ifndef HECK_GAME_H
#define HECK_GAME_H

#include "actor.h"
#include "keyboard.h"
#include <SDL2/SDL2_framerate.h>
#include <memory>
#include <vector>

namespace nsd {
class Graphics;

class Atlas;

class Map;

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

  void turn();

  void render();

private:
  FPSmanager fpsManager_{};

  std::unique_ptr<Graphics> graphics_{nullptr};

  std::unique_ptr<Atlas> atlas_{nullptr};

  std::unique_ptr<Map> map_{nullptr};

  bool isRunning_{true};

  Keyboard keyboard_{};

  std::vector<std::unique_ptr<Actor>> actors_{};

  size_t currentActor_{0};
};
} // namespace nsd

#endif
