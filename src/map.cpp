#include "map.h"
#include "graphics.h"
#include <utility>

namespace nsd {
Map::Map(int width, int height, std::unique_ptr<Tileset> tileset)
    : map_(width, height), tileset_(std::move(tileset)), tiles_(width * height) {
  for (auto x{0}; x < width; ++x) {
    for (auto y{0}; y < height; ++y) {
      auto &tile{tiles_[getTileIndex(x, y)]};

      tile.tileId = 77;
      tile.position = glm::ivec2{x, y};
      tile.color = glm::u8vec4{0x88, 0x88, 0x88, 0xFF};
    }
  }
}

void Map::render(Graphics &graphics) const {
  for (const auto &tile : tiles_) {
    tileset_->blitTile(tile, true, true, graphics);
  }
}

void Map::dig(int startX, int startY, int endX, int endY) {
  if (endX < startX) {
    std::swap(startX, endX);
  }

  if (endY < startY) {
    std::swap(startY, endY);
  }

  for (auto x{0}; x < map_.getWidth(); ++x) {
    for (auto y{0}; y < map_.getHeight(); ++y) {
      if (x >= startX && x <= endX && y >= startY && y <= endY) {
        map_.setProperties(x, y, true, true);

        auto &tile{tiles_[getTileIndex(x, y)]};

        tile.tileId = 105;
      }
    }
  }
}

void Map::createRoom(int startX, int startY, int endX, int endY, bool isFirstRoom) {
  dig(startX, startY, endX, endY);

  if (isFirstRoom) {
    // TODO: set player start position
  }

  // TODO: Populate rooms.
}

size_t Map::getTileIndex(int x, int y) const { return (y * map_.getWidth()) + x; }

} // namespace nsd
