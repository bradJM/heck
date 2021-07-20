#include "bsp_generator.h"
#include "map.h"
#include <libtcod/mersenne.hpp>

namespace nsd {
constexpr auto MAX_ROOM_SIZE{12};
constexpr auto MIN_ROOM_SIZE{6};
constexpr auto MAX_ROOM_ENEMIES{3};

BspGenerator::BspGenerator(Map *map) : map_(map) {}

const MapInfo &BspGenerator::generate() {
  auto bsp{TCODBsp{0, 0, map_->getWidth(), map_->getHeight()}};
  bsp.splitRecursive(TCODRandom::getInstance(), 8, MAX_ROOM_SIZE, MIN_ROOM_SIZE, 1.5F, 1.5F);
  bsp.traverseInvertedLevelOrder(this, nullptr);

  return mapInfo_;
}

bool BspGenerator::visitNode(TCODBsp *node, [[maybe_unused]] void *userData) {
  if (!node->isLeaf()) {
    return true;
  }

  auto *rng{TCODRandom::getInstance()};
  auto width{rng->getInt(MIN_ROOM_SIZE, node->w - 2)};
  auto height{rng->getInt(MIN_ROOM_SIZE, node->h - 2)};
  auto startX{rng->getInt(node->x + 1, node->x + node->w - width - 1)};
  auto startY{rng->getInt(node->y - 1, node->y + node->h - height - 1)};
  auto endX{startX + width - 1};
  auto endY{startY + height - 1};
  auto centerX{startX + (width / 2)};
  auto centerY{startY + (height / 2)};
  auto isFirstRoom{mapInfo_.generatedRooms == 0};

  map_->createRoom(startX, startY, endX, endY);

  if (isFirstRoom) {
    mapInfo_.playerStart.x = startX + ((endX - startX) / 2);
    mapInfo_.playerStart.y = startY + ((endY - startY) / 2);
  } else {
    // dig connecting corridors.
    map_->dig(lastCenterX_, lastCenterY_, centerX, lastCenterY_);
    map_->dig(centerX, lastCenterY_, centerX, centerY);

    // set spawn positions for enemies
    auto numEnemies{rng->getInt(0, MAX_ROOM_ENEMIES)};

    while (numEnemies > 0) {
      auto x{rng->getInt(startX, endX)};
      auto y{rng->getInt(startY, endY)};

      mapInfo_.enemySpawns.emplace_back(x, y);

      --numEnemies;
    }
  }

  ++mapInfo_.generatedRooms;
  lastCenterX_ = centerX;
  lastCenterY_ = centerY;

  return true;
}
} // namespace nsd
