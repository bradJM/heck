#include "bsp_generator.h"
#include "map.h"
#include <libtcod/mersenne.hpp>

namespace nsd {
static const int MAX_ROOM_SIZE = 12;
static const int MIN_ROOM_SIZE = 6;

BspGenerator::BspGenerator(Map *map) : map_(map) {}

void BspGenerator::generate() {
  auto bsp{TCODBsp{0, 0, map_->getWidth(), map_->getHeight()}};
  bsp.splitRecursive(TCODRandom::getInstance(), 8, MAX_ROOM_SIZE, MIN_ROOM_SIZE, 1.5F, 1.5F);
  bsp.traverseInvertedLevelOrder(this, nullptr);
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
  auto isFirstRoom{roomNumber_ == 0};

  map_->createRoom(startX, startY, endX, endY, isFirstRoom);

  if (!isFirstRoom) {
    // dig connecting corridors.
    map_->dig(lastCenterX_, lastCenterY_, centerX, lastCenterY_);
    map_->dig(centerX, lastCenterY_, centerX, centerY);
  }

  ++roomNumber_;
  lastCenterX_ = centerX;
  lastCenterY_ = centerY;

  return true;
}
} // namespace nsd
