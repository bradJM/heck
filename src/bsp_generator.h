#ifndef HECK_BSP_GENERATOR_H
#define HECK_BSP_GENERATOR_H

#include "map.h"
#include <libtcod/bsp.hpp>

namespace nsd {

class BspGenerator : public ITCODBspCallback {
public:
  explicit BspGenerator(Map *map_);

  const MapInfo &generate();

  bool visitNode(TCODBsp *node, [[maybe_unused]] void *userData) override;

private:
  Map *map_;

  MapInfo mapInfo_{};

  int lastCenterX_{0};

  int lastCenterY_{0};
};
} // namespace nsd

#endif
