#ifndef HECK_COMPONENT_H
#define HECK_COMPONENT_H

namespace nsd {
class Actor;

class Graphics;

class Component {
public:
  Component(const Component &other) = delete;

  Component(Component &&other) = default;

  virtual ~Component() = default;

  Component &operator=(const Component &other) = delete;

  Component &operator=(Component &&other) = delete;

  virtual void update([[maybe_unused]] float deltaTime) {}

  virtual void render([[maybe_unused]] Graphics &graphics) {}

protected:
  explicit Component(Actor &owner) : owner_(owner) {}

  Actor &getOwner() { return owner_; }

private:
  Actor &owner_;
};
} // namespace nsd

#endif
