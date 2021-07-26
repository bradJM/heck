#include "map.h"
#include "bsp_generator.h"
#include "graphics.h"
#include <algorithm>
#include <utility>

namespace nsd {
constexpr auto fovRange{8};

Map::Map(int width, int height) : map_(width, height), tiles_(width * height) {
  for (auto x{0}; x < width; ++x) {
    for (auto y{0}; y < height; ++y) {
      auto &tile{tiles_[getTileIndex(x, y)]};

      tile.tileId = 77;
      tile.isVisible = false;
      tile.isExplored = false;
      tile.position = glm::ivec2{x, y};
      tile.color = glm::u8vec4{0x96, 0x3C, 0x3C, 0xFF};
    }
  }

  auto generator{BspGenerator{}};
  generator.generate(*this);
}

bool Map::isWalkable(const glm::ivec2 &position) const {
  if (position.x < 0 || position.x >= map_.getWidth()) {
    return false;
  }

  if (position.y < 0 || position.y >= map_.getHeight()) {
    return false;
  }

  return map_.isWalkable(position.x, position.y);
}

bool Map::isInFov(const glm::ivec2 &position) const { return map_.isInFov(position.x, position.y); }

void Map::computeFov(const glm::ivec2 &position, int radius) {
  map_.computeFov(position.x, position.y, radius);

  for (auto &tile : tiles_) {
    tile.isVisible = map_.isInFov(tile.position.x, tile.position.y);
    tile.isExplored = tile.isExplored || tile.isVisible;
  }

  isFovDirty_ = false;
}

void Map::turn() {
  if (isFovDirty_) {
    computeFov(playerPosition_, fovRange);
  }

  actors_.turn();
}

void Map::render(Graphics &graphics) const {
  for (const auto &tile : tiles_) {
    graphics.blitTile(tile);
  }

  actors_.render(graphics);
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
        tile.color = glm::u8vec4{0x3A, 0x28, 0x02, 0xFF};
      }
    }
  }
}

void Map::onPlayerAdded(const Actor &player) {
  playerId_ = player.getId();
  playerPosition_ = player.getPosition();
}

void Map::onActorMoved(const Actor &actor) {
  isFovDirty_ = true;

  if (actor.getId() == playerId_) {
    playerPosition_ = actor.getPosition();
  }
}

size_t Map::getTileIndex(int x, int y) const { return (y * map_.getWidth()) + x; }
} // namespace nsd
