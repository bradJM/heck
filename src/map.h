#ifndef HECK_MAP_H
#define HECK_MAP_H

#include "actor_collection.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <libtcod/fov.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace nsd {
class Actor;

class Graphics;

struct Tile {
  int tileId;

  bool isVisible;

  bool isExplored;

  glm::ivec2 position;

  glm::u8vec4 color;
};

class Map {
public:
  Map(int width, int height);

  bool isWalkable(const glm::ivec2 &position) const;

  bool isInFov(const glm::ivec2 &position) const;

  void computeFov(const glm::ivec2 &position, int radius);

  void turn();

  void render(Graphics &graphics) const;

  void dig(int startX, int startY, int endX, int endY);

  Actor &addActor(Actor &&actor) { return actors_.add(std::move(actor)); }

  void onPlayerAdded(const Actor &player);

  void onActorMoved(const Actor &actor);

  int getWidth() const { return map_.getWidth(); }

  int getHeight() const { return map_.getHeight(); }

private:
  TCODMap map_;

  std::vector<Tile> tiles_;

  ActorCollection actors_{this};

  bool isFovDirty_{true};

  int playerId_{0};

  glm::ivec2 playerPosition_{0};

  size_t getTileIndex(int x, int y) const;
};
} // namespace nsd

#endif
