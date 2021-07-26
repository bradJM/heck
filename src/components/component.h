#ifndef HECK_COMPONENT_H
#define HECK_COMPONENT_H

#include <memory>

namespace nsd {
class Action;

class Actor;

class Game;

class Graphics;

class Component {
public:
  Component(const Component &other) = delete;

  Component(Component &&other) = delete;

  virtual ~Component() = default;

  Component &operator=(const Component &other) = delete;

  Component &operator=(Component &&other) = delete;

  virtual std::unique_ptr<Action> produceAction() { return nullptr; }

  virtual void render([[maybe_unused]] const Actor &owner, [[maybe_unused]] Graphics &graphics) {}

protected:
  Component() = default;
};
} // namespace nsd

#endif
