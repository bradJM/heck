#ifndef HECK_ACTION_H
#define HECK_ACTION_H

#include <cassert>
#include <memory>

namespace nsd {
class Actor;

class ActorCollection;

class Action;

class Game;

class Map;

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

  virtual ActionResult perform(Actor &actor, ActorCollection &actors, Map &map) = 0;

protected:
  Action() = default;
};
} // namespace nsd

#endif
