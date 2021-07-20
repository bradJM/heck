#ifndef HECK_TILESET_H
#define HECK_TILESET_H

#include "graphics.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace nsd {

struct Tile {
  int tileId;

  bool isVisible;

  bool isExplored;

  glm::ivec2 position;

  glm::u8vec4 color;
};

class Tileset {
public:
  explicit Tileset(Atlas *atlas);

  void blitTile(const Tile &tile, Graphics &graphics) const;

private:
  Atlas *atlas_;
};
} // namespace nsd

#endif
