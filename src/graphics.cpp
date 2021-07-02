#include "graphics.h"
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <cstdint>

namespace nsd {
Graphics::Graphics() {
  window_.reset(createWindow(800, 500, 0));
  renderer_.reset(createRenderer(window_.get(), 800, 500));
}

TextureInfo Graphics::loadTexture(const std::string &path) {
  auto width{0};
  auto height{0};
  auto *texture{IMG_LoadTexture(renderer_.get(), path.c_str())};

  // check errors

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  return TextureInfo{texture, width, height};
}

void Graphics::prepare() {
  SDL_SetRenderDrawColor(renderer_.get(), 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer_.get());
}

void Graphics::blit(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect,
                    const glm::u8vec4 &color) {
  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
  SDL_SetTextureAlphaMod(texture, color.a);

  SDL_RenderCopy(renderer_.get(), texture, &sourceRect, &destRect);

  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
  SDL_SetTextureAlphaMod(texture, color.a);
}

void Graphics::present() { SDL_RenderPresent(renderer_.get()); }

SDL_Window *Graphics::createWindow(int width, int height, std::uint32_t flags) {
  auto *window{SDL_CreateWindow("Heck!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                                height, flags)};

  // check errors

  return window;
}

SDL_Renderer *Graphics::createRenderer(SDL_Window *window, int logicalWidth, int logicalHeight) {
  auto *renderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)};

  // check errors

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
  SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

  return renderer;
}

Atlas::Atlas(const std::string &texturePath, Graphics &graphics, int elementWidth,
             int elementHeight)
    : elementWidth_(elementWidth), elementHeight_(elementHeight) {
  textureInfo_ = graphics.loadTexture(texturePath);

  rows_ = textureInfo_.height / elementHeight_;
  columns_ = textureInfo_.width / elementWidth_;
  totalElements_ = rows_ * columns_;
}

SDL_Rect Atlas::getSourceRectangle(int elementId) {
  const auto cursor{elementId % totalElements_};
  const auto sourceX{(cursor % columns_) * elementWidth_};
  const auto sourceY{(cursor / columns_) * elementHeight_};

  return SDL_Rect{sourceX, sourceY, elementWidth_, elementHeight_};
}

SDL_Rect Atlas::getDestinationRectangle(const glm::ivec2 &position) {
  return SDL_Rect{position.x * elementWidth_, position.y * elementHeight_, elementWidth_,
                  elementHeight_};
}
} // namespace nsd
