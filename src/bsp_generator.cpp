#include "bsp_generator.h"
#include "actor_factory.h"
#include "map.h"
#include <glm/vec2.hpp>
#include <libtcod/mersenne.hpp>

namespace nsd {
constexpr auto MAX_ROOM_SIZE{12};
constexpr auto MIN_ROOM_SIZE{6};
constexpr auto MAX_ROOM_ENEMIES{3};

void BspGenerator::generate(Map &map) {
  auto bsp{TCODBsp{0, 0, map.getWidth(), map.getHeight()}};
  bsp.splitRecursive(TCODRandom::getInstance(), 8, MAX_ROOM_SIZE, MIN_ROOM_SIZE, 1.5F, 1.5F);
  bsp.traverseInvertedLevelOrder(this, &map);
}

bool BspGenerator::visitNode(TCODBsp *node, void *userData) {
  if (!node->isLeaf()) {
    return true;
  }

  const auto &actorFactory{ActorFactory::getInstance()};
  auto *map{static_cast<Map *>(userData)};
  auto *rng{TCODRandom::getInstance()};
  auto width{rng->getInt(MIN_ROOM_SIZE, node->w - 2)};
  auto height{rng->getInt(MIN_ROOM_SIZE, node->h - 2)};
  auto startX{rng->getInt(node->x + 1, node->x + node->w - width - 1)};
  auto startY{rng->getInt(node->y - 1, node->y + node->h - height - 1)};
  auto endX{startX + width - 1};
  auto endY{startY + height - 1};
  auto centerX{startX + (width / 2)};
  auto centerY{startY + (height / 2)};
  auto isFirstRoom{generatedRooms_ == 0};

  // Carve out a room.
  map->dig(startX, startY, endX, endY);

  if (isFirstRoom) {
    auto spawnPosition{glm::ivec2{0}};
    spawnPosition.x = startX + ((endX - startX) / 2);
    spawnPosition.y = startY + ((endY - startY) / 2);

    const auto &player{map->addActor(actorFactory.spawnActor("player", spawnPosition))};
    map->onPlayerAdded(player);
  } else {
    // dig connecting corridors.
    map->dig(lastCenterX_, lastCenterY_, centerX, lastCenterY_);
    map->dig(centerX, lastCenterY_, centerX, centerY);

    // set spawn positions for enemies
    auto numEnemies{rng->getInt(0, MAX_ROOM_ENEMIES)};

    while (numEnemies > 0) {
      auto spawnPosition{glm::ivec2{0}};
      spawnPosition.x = rng->getInt(startX, endX);
      spawnPosition.y = rng->getInt(startY, endY);

      if (map->isWalkable(spawnPosition)) {
        if (rng->getInt(0, 100) < 80) {
          map->addActor(actorFactory.spawnActor("imp", spawnPosition));
        } else {
          map->addActor(actorFactory.spawnActor("horned demon", spawnPosition));
        }
      }

      --numEnemies;
    }
  }

  ++generatedRooms_;
  lastCenterX_ = centerX;
  lastCenterY_ = centerY;

  return true;
}
} // namespace nsd
