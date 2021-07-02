// Credit: https://thatgamesguy.co.uk/cpp-game-dev-7/
#ifndef HECK_ACTOR_H
#define HECK_ACTOR_H

#include "component.h"
#include <glm/vec2.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace nsd {
class Graphics;

class Actor {
public:
  explicit Actor(const glm::ivec2 &position = glm::ivec2{0});

  void update(float deltaTime);

  void render(Graphics &graphics) const;

  template <typename T, typename... Tn> std::shared_ptr<T> addComponent(Tn &&...args) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    auto newComponent = std::make_shared<T>(*this, std::forward<Tn>(args)...);

    // If we already have a component of this type, then replace it.
    for (auto &component : components_) {
      if (std::dynamic_pointer_cast<T>(component)) {
        component = newComponent;

        return std::dynamic_pointer_cast<T>(component);
      }
    }

    // Otherwise, add it.
    components_.push_back(newComponent);

    return newComponent;
  }

  template <typename T> std::shared_ptr<T> getComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    for (auto &component : components_) {
      if (std::dynamic_pointer_cast<T>(component)) {
        return std::dynamic_pointer_cast<T>(component);
      }
    }

    return nullptr;
  }

  const glm::ivec2 &getPosition() const { return position_; }

  void setPosition(const glm::ivec2 &position) { position_ = position; }

private:
  glm::ivec2 position_;

  std::vector<std::shared_ptr<Component>> components_{};
};
} // namespace nsd

#endif
