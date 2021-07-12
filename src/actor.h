#ifndef HECK_ACTOR_H
#define HECK_ACTOR_H

#include <memory>
#include <vector>

namespace nsd {
class Graphics;

class Action;

class Component;

class Actor {
public:
  explicit Actor(int speed = 100, int startingEnergy = 0);

  bool refresh();

  void spendEnergy(int amount);

  std::unique_ptr<Action> turn();

  void render(Graphics &graphics) const;

  template <typename T, typename... Args> std::shared_ptr<T> addComponent(Args &&...args) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    auto newComponent{std::make_shared<T>(this, std::forward<Args>(args)...)};

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

private:
  int speed_;

  int energy_;

  std::vector<std::shared_ptr<Component>> components_;
};
} // namespace nsd

#endif
