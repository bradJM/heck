#ifndef HECK_GRAPHICS_H
#define HECK_GRAPHICS_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <string>

struct SDL_Rect;

namespace nsd {
struct TextureInfo {
  SDL_Texture *texture{nullptr};

  int width{0};

  int height{0};
};

class Graphics {
public:
  using WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

  using RendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

  Graphics();

  TextureInfo loadTexture(const std::string &path);

  void prepare();

  void blit(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect,
            const glm::u8vec4 &color);

  void present();

private:
  static SDL_Window *createWindow(int width, int height, Uint32 flags);

  static SDL_Renderer *createRenderer(SDL_Window *window, int logicalWidth, int logicalHeight);

  WindowPtr window_{nullptr, SDL_DestroyWindow};

  RendererPtr renderer_{nullptr, SDL_DestroyRenderer};
};

class Atlas {
public:
  Atlas(const std::string &texturePath, Graphics &graphics, int elementWidth, int elementHeight);

  SDL_Rect getSourceRectangle(int elementId);

  SDL_Rect getDestinationRectangle(const glm::ivec2 &position);

  SDL_Texture *getTexture() const { return textureInfo_.texture; }

private:
  int elementWidth_;

  int elementHeight_;

  TextureInfo textureInfo_{nullptr};

  int rows_{0};

  int columns_{0};

  int totalElements_{0};
};
} // namespace nsd

#endif
