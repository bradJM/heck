#ifndef HECK_BSP_GENERATOR_H
#define HECK_BSP_GENERATOR_H

#include <libtcod/bsp.hpp>

namespace nsd {
class Map;

class BspGenerator : public ITCODBspCallback {
public:
  void generate(Map &map);

  bool visitNode(TCODBsp *node, void *userData) override;

private:
  int generatedRooms_{0};

  int lastCenterX_{0};

  int lastCenterY_{0};
};
} // namespace nsd

#endif
