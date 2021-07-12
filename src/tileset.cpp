#include "tileset.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cassert>
#include <cstdint>

namespace nsd {
Tileset::Tileset(Atlas *atlas) : atlas_(atlas) {}

void Tileset::blitTile(const Tile &tile, bool isVisible, bool isExplored,
                       Graphics &graphics) const {
  const auto sourceRect{atlas_->getSourceRectangle(tile.tileId)};
  const auto destRect{atlas_->getDestinationRectangle(tile.position)};

  // Tiles that are currently visible render at full color, tiles that have been explored render at
  // 50% color, and other tiles are invisible.
  const auto mod{isVisible ? 1.0F : isExplored ? 0.5F : 0.0F};
  const auto r{static_cast<std::uint8_t>(static_cast<float>(tile.color.r) * mod)};
  const auto g{static_cast<std::uint8_t>(static_cast<float>(tile.color.g) * mod)};
  const auto b{static_cast<std::uint8_t>(static_cast<float>(tile.color.b) * mod)};
  const auto finalColor{glm::u8vec4{r, g, b, tile.color.a}};

  graphics.blit(atlas_->getTexture(), sourceRect, destRect, finalColor);
}
} // namespace nsd
