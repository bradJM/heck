#ifndef HECK_BSP_GENERATOR_H
#define HECK_BSP_GENERATOR_H

#include <libtcod/bsp.hpp>

namespace nsd {
class Map;

class BspGenerator : public ITCODBspCallback {
public:
  explicit BspGenerator(Map *map_);

  void generate();

  bool visitNode(TCODBsp *node, [[maybe_unused]] void *userData) override;

private:
  Map *map_;

  int roomNumber_{0};

  int lastCenterX_{0};

  int lastCenterY_{0};
};
} // namespace nsd

#endif
