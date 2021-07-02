#ifndef HECK_TILESET_H
#define HECK_TILESET_H

#include "graphics.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace nsd {

class Tileset {
public:
  Tileset(const std::string &texturePath, Graphics &graphics, int tileWidth, int tileHeight);

  void blitTile(int tileId, const glm::ivec2 &position, const glm::u8vec4 &color, bool isVisible,
                bool isExplored, Graphics &graphics);

private:
  Atlas atlas_;
};
} // namespace nsd

#endif
