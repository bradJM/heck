#ifndef HECK_ACTOR_H
#define HECK_ACTOR_H

#include <glm/vec2.hpp>
#include <memory>
#include <vector>

namespace nsd {
class Game;

class Graphics;

class Action;

class Component;

class Actor {
public:
  Actor(const glm::ivec2 &position, int speed, int startingEnergy, bool blocksMovement);

  bool operator==(const Actor &other) const { return id_ == other.id_; }

  bool operator!=(const Actor &other) const { return !(*this == other); }

  int getId() const { return id_; }

  const glm::ivec2 &getPosition() const { return position_; }

  void move(const glm::ivec2 &direction);

  bool blocks(const Actor &other) const;

  bool refresh();

  void spendEnergy(int amount);

  std::unique_ptr<Action> turn();

  void render(Graphics &graphics) const;

  template <typename T, typename... Args> std::shared_ptr<T> addComponent(Args &&...args) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    auto newComponent{std::make_shared<T>(std::forward<Args>(args)...)};

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

  template <typename T> std::shared_ptr<T> getComponent() const {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    for (const auto &component : components_) {
      if (std::dynamic_pointer_cast<T>(component)) {

        return std::dynamic_pointer_cast<T>(component);
      }
    }

    return nullptr;
  }

private:
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
  static inline auto nextId_{0};

  int id_;

  glm::ivec2 position_;

  int speed_;

  int energy_;

  bool blocksMovement_;

  std::vector<std::shared_ptr<Component>> components_{};
};
} // namespace nsd

#endif
