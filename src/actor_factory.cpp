#include "actor_factory.h"
#include <fstream>
#include <glm/vec2.hpp>
#include <nlohmann/json.hpp>

namespace nsd {
ActorFactory::ActorFactory() {
  auto jsonStream{std::ifstream{"resources/archetypes.json"}};
  auto json{nlohmann::json{}};

  jsonStream >> json;

  archetypes_ = json.get<std::map<std::string, Archetype>>();
}

Actor ActorFactory::spawnActor(const std::string &archetype, const glm::ivec2 &position) const {
  return archetypes_.at(archetype).spawnActor(position);
}
} // namespace nsd
