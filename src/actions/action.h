#ifndef HECK_ACTION_H
#define HECK_ACTION_H

#include <cassert>
#include <memory>

namespace nsd {
class Actor;

class Action;

struct ActionResult {
  bool succeeded{false};

  std::unique_ptr<Action> alternative{nullptr};
};

class Action {
public:
  Action(const Action &other) = delete;

  Action(Action &&other) = delete;

  virtual ~Action() = default;

  Action &operator=(const Action &other) = delete;

  Action &operator=(Action &&other) = delete;

  virtual ActionResult perform() = 0;

protected:
  explicit Action(Actor *owner) : owner_(owner) {}

  Actor *getOwner() {
    assert(owner_ != nullptr);

    return owner_;
  }

private:
  Actor *owner_;
};
} // namespace nsd

#endif
