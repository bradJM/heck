#ifndef HECK_ARCHETYPE_H
#define HECK_ARCHETYPE_H

#include "actor.h"
#include <glm/vec2.hpp>
#include <nlohmann/json.hpp>

namespace nsd {
class Archetype {
public:
  Actor spawnActor(glm::ivec2 position) const;

private:
  friend void from_json(const nlohmann::json &json, Archetype &archetype);

  bool takesInput_;

  int speed_;

  int startingEnergy_;

  bool blocksMovement_;

  int spriteIndex_;

  int r_;

  int g_;

  int b_;

  int a_;
};

void from_json(const nlohmann::json &json, Archetype &archetype);
} // namespace nsd

#endif
