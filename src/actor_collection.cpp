#include "actor_collection.h"
#include "actions/action.h"
#include "game.h"
#include "graphics.h"
#include "map.h"
#include <algorithm>
#include <glm/vec2.hpp>
#include <memory>
#include <utility>

namespace nsd {
ActorCollection::ActorCollection(Map *map) : map_(map) {}

Actor &ActorCollection::add(Actor &&actor) {
  actors_.push_back(std::move(actor));

  return actors_.back();
}

void ActorCollection::clear() { actors_.clear(); }

bool ActorCollection::checkAny(const std::function<bool(const Actor &)> &predicate) {
  return std::any_of(std::cbegin(actors_), std::cend(actors_), predicate);
}

bool ActorCollection::checkAll(const std::function<bool(const Actor &)> &predicate) {
  return std::all_of(std::cbegin(actors_), std::cend(actors_), predicate);
}

void ActorCollection::turn() {
  if (actors_.empty()) {
    return;
  }

  auto &actor{actors_[currentActor_]};
  auto action{actor.turn()};

  // We're still waiting for this actor to produce an action, so don't advance.
  if (action == nullptr) {
    return;
  }

  while (true) {
    auto result{action->perform(actor, *this, *map_)};

    // The action failed, so this actor should get another chance to act.
    if (!result.succeeded) {
      return;
    }

    // We've exhausted alternative actions and the final one succeeded. We're done!
    if (result.alternative == nullptr) {
      break;
    }

    action.swap(result.alternative);
  }

  currentActor_ = (currentActor_ + 1) % actors_.size();
}

void ActorCollection::render(Graphics &graphics) const {
  for (const auto &actor : actors_) {
    if (map_->isInFov(actor.getPosition())) {
      actor.render(graphics);
    }
  }
}
} // namespace nsd
