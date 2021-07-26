#ifndef HECK_GAME_H
#define HECK_GAME_H

#include <SDL2/SDL2_framerate.h>
#include <memory>

namespace nsd {
class Graphics;

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

  Map &getMap() const { return *map_; }

private:
  FPSmanager fpsManager_{};

  std::unique_ptr<Graphics> graphics_{nullptr};

  std::unique_ptr<Map> map_{nullptr};

  bool isRunning_{true};
};
} // namespace nsd

#endif
