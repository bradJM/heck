#ifndef HECK_GRAPHICS_H
#define HECK_GRAPHICS_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <string>
#include <utility>

namespace nsd {
struct TextureInfo {
  SDL_Texture *texture{nullptr};

  int width{0};

  int height{0};
};

class Atlas;

struct Tile;

class Graphics {
public:
  using WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

  using RendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

  Graphics();

  TextureInfo loadTexture(const std::string &path);

  void prepare();

  void blit(const SDL_Rect &sourceRect, const SDL_Rect &destRect, const glm::u8vec4 &color);

  void blit(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect,
            const glm::u8vec4 &color);

  void blitSprite(int spriteIndex, const glm::ivec2 &position, const glm::u8vec4 &color);

  void blitTile(const Tile &tile);

  void present();

private:
  static SDL_Window *createWindow(int width, int height, Uint32 flags);

  static SDL_Renderer *createRenderer(SDL_Window *window, int logicalWidth, int logicalHeight);

  WindowPtr window_{nullptr, SDL_DestroyWindow};

  RendererPtr renderer_{nullptr, SDL_DestroyRenderer};

  std::unique_ptr<Atlas> atlas_{nullptr};
};

class Atlas {
public:
  Atlas(const TextureInfo &textureInfo, int elementWidth, int elementHeight);

  SDL_Rect getSourceRectangle(int elementId) const;

  SDL_Rect getDestinationRectangle(const glm::ivec2 &position) const;

  SDL_Texture *getTexture() const { return textureInfo_.texture; }

private:
  TextureInfo textureInfo_;

  int elementWidth_;

  int elementHeight_;

  int rows_{0};

  int columns_{0};

  int totalElements_{0};
};
} // namespace nsd

#endif
