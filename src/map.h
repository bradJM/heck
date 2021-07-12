#ifndef HECK_MAP_H
#define HECK_MAP_H

#include "tileset.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <libtcod/fov.hpp>
#include <vector>

namespace nsd {
class Graphics;

class Map {
public:
  Map(int width, int height, std::unique_ptr<Tileset> tileset);

  void render(Graphics &graphics) const;

  void dig(int startX, int startY, int endX, int endY);

  void createRoom(int startX, int startY, int endX, int endY, bool isFirstRoom);

  int getWidth() const { return map_.getWidth(); }

  int getHeight() const { return map_.getHeight(); }

private:
  TCODMap map_;

  std::unique_ptr<Tileset> tileset_;

  std::vector<Tile> tiles_;

  size_t getTileIndex(int x, int y) const;
};
} // namespace nsd

#endif
