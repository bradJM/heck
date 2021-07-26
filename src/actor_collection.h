#ifndef HECK_ACTOR_COLLECTION_H
#define HECK_ACTOR_COLLECTION_H

#include "actor.h"
#include <functional>
#include <vector>

namespace nsd {
class Graphics;

class Map;

class ActorCollection {
public:
  explicit ActorCollection(Map *map);

  Actor &add(Actor &&actor);

  void clear();

  bool checkAny(const std::function<bool(const Actor &)> &predicate);

  bool checkAll(const std::function<bool(const Actor &)> &predicate);

  void turn();

  void render(Graphics &graphics) const;

  size_t size() { return actors_.size(); }

private:
  Map *map_;

  std::vector<Actor> actors_{};

  size_t currentActor_{0};
};
} // namespace nsd

#endif
