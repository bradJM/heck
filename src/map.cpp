#include "map.h"
#include "actor.h"
#include "components/transform_component.h"
#include "graphics.h"
#include <algorithm>
#include <utility>

namespace nsd {
Map::Map(int width, int height, std::unique_ptr<Tileset> tileset,
         const std::vector<std::unique_ptr<Actor>> *actors)
    : map_(width, height), tileset_(std::move(tileset)), tiles_(width * height), actors_(actors) {
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
}

bool Map::isWalkable(const glm::ivec2 &position) const {
  if (position.x < 0 || position.x >= map_.getWidth()) {
    return false;
  }

  if (position.y < 0 || position.y >= map_.getHeight()) {
    return false;
  }

  if (!map_.isWalkable(position.x, position.y)) {
    return false;
  }

  return std::none_of(actors_->begin(), actors_->end(), [&position](const auto &actor) {
    const auto &transform{actor->template getComponent<TransformComponent>()};

    return transform->getPosition() == position && transform->blocksMovement();
  });
}

bool Map::isInFov(const glm::ivec2 &position) const { return map_.isInFov(position.x, position.y); }

void Map::computeFov([[maybe_unused]] const glm::ivec2 &position, [[maybe_unused]] int radius) {
  map_.computeFov(position.x, position.y, radius);

  for (auto &tile : tiles_) {
    tile.isVisible = map_.isInFov(tile.position.x, tile.position.y);
    tile.isExplored = tile.isExplored || tile.isVisible;
  }
}

void Map::render(Graphics &graphics) const {
  for (const auto &tile : tiles_) {
    tileset_->blitTile(tile, graphics);
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
        tile.color = glm::u8vec4{0x3A, 0x28, 0x02, 0xFF};
      }
    }
  }
}

void Map::createRoom(int startX, int startY, int endX, int endY) {
  dig(startX, startY, endX, endY);

  // TODO: Populate rooms.
}

size_t Map::getTileIndex(int x, int y) const { return (y * map_.getWidth()) + x; }

} // namespace nsd
