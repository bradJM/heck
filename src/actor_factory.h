#ifndef HECK_ACTOR_FACTORY_H
#define HECK_ACTOR_FACTORY_H

#include "actor.h"
#include "archetype.h"
#include "singleton.h"
#include <map>
#include <string>

namespace nsd {
class ActorFactory : public Singleton<ActorFactory> {
public:
  ActorFactory();

  Actor spawnActor(const std::string &archetype, const glm::ivec2 &position) const;

private:
  std::map<std::string, Archetype> archetypes_{};
};
} // namespace nsd

#endif
