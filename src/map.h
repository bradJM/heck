#ifndef HECK_MAP_H
#define HECK_MAP_H

#include "tileset.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <libtcod/fov.hpp>
#include <memory>
#include <vector>

namespace nsd {
class Actor;

class Graphics;

struct MapInfo {
  glm::ivec2 playerStart{0};

  std::vector<glm::ivec2> enemySpawns{};

  int generatedRooms{0};
};

class Map {
public:
  // TODO: This is really messy. Wrap the actor vector up and pass that instead or something.
  Map(int width, int height, std::unique_ptr<Tileset> tileset,
      const std::vector<std::unique_ptr<Actor>> *actors);

  bool isWalkable(const glm::ivec2 &position) const;

  bool isInFov(const glm::ivec2 &position) const;

  void computeFov(const glm::ivec2 &position, int radius);

  void render(Graphics &graphics) const;

  void dig(int startX, int startY, int endX, int endY);

  void createRoom(int startX, int startY, int endX, int endY);

  int getWidth() const { return map_.getWidth(); }

  int getHeight() const { return map_.getHeight(); }

private:
  TCODMap map_;

  std::unique_ptr<Tileset> tileset_;

  std::vector<Tile> tiles_;

  const std::vector<std::unique_ptr<Actor>> *actors_;

  size_t getTileIndex(int x, int y) const;
};
} // namespace nsd

#endif
