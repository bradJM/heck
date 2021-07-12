#ifndef HECK_COMPONENT_H
#define HECK_COMPONENT_H

#include <cassert>
#include <memory>

namespace nsd {
class Action;

class Actor;

class Graphics;

class Component {
public:
  Component(const Component &other) = delete;

  Component(Component &&other) = delete;

  virtual ~Component() = default;

  Component &operator=(const Component &other) = delete;

  Component &operator=(Component &&other) = delete;

  virtual std::unique_ptr<Action> produceAction() { return nullptr; }

  virtual void render([[maybe_unused]] Graphics &graphics) {}

protected:
  explicit Component(Actor *owner) : owner_(owner) {}

  Actor *getOwner() {
    assert(owner_ != nullptr);

    return owner_;
  }

private:
  Actor *owner_;
};
} // namespace nsd

#endif
