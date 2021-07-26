#include "archetype.h"
#include "components/ai_component.h"
#include "components/keyboard_input_component.h"
#include "components/sprite_component.h"
#include <glm/vec4.hpp>

namespace nsd {
Actor Archetype::spawnActor(glm::ivec2 position) const {
  auto actor{Actor{position, speed_, startingEnergy_, blocksMovement_}};

  actor.addComponent<SpriteComponent>(spriteIndex_, glm::u8vec4{r_, g_, b_, a_});

  if (takesInput_) {
    actor.addComponent<KeyboardInputComponent>();
  } else {
    actor.addComponent<AiComponent>();
  }

  return actor;
}

void from_json(const nlohmann::json &json, Archetype &archetype) {
  json.at("takesInput").get_to(archetype.takesInput_);
  json.at("speed").get_to(archetype.speed_);
  json.at("startingEnergy").get_to(archetype.startingEnergy_);
  json.at("blocksMovement").get_to(archetype.blocksMovement_);
  json.at("spriteIndex").get_to(archetype.spriteIndex_);
  json.at("r").get_to(archetype.r_);
  json.at("g").get_to(archetype.g_);
  json.at("b").get_to(archetype.b_);
  json.at("a").get_to(archetype.a_);
}
} // namespace nsd
