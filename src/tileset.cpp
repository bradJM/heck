#include "tileset.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cassert>
#include <cstdint>

namespace nsd {
Tileset::Tileset(const std::string &texturePath, Graphics &graphics, int tileWidth, int tileHeight)
    : atlas_(texturePath, graphics, tileWidth, tileHeight) {}

void Tileset::blitTile(int tileId, const glm::ivec2 &position, const glm::u8vec4 &color,
                       bool isVisible, bool isExplored, Graphics &graphics) {
  const auto sourceRect{atlas_.getSourceRectangle(tileId)};
  const auto destRect{atlas_.getDestinationRectangle(position)};

  // Tiles that are currently visible render at full color, tiles that have been explored render at
  // 50% color, and other tiles are invisible.
  const auto mod{isVisible ? 1.0F : isExplored ? 0.5F : 0.0F};
  const auto r{static_cast<std::uint8_t>(static_cast<float>(color.r) * mod)};
  const auto g{static_cast<std::uint8_t>(static_cast<float>(color.g) * mod)};
  const auto b{static_cast<std::uint8_t>(static_cast<float>(color.b) * mod)};
  const auto finalColor{glm::u8vec4{r, g, b, color.a}};

  graphics.blit(atlas_.getTexture(), sourceRect, destRect, finalColor);
}
} // namespace nsd
