#include "game.h"
#include "graphics.h"
#include "keyboard_input_component.h"
#include "sprite_component.h"
#include "tileset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>

namespace nsd {
constexpr auto fps = 60;
constexpr auto tileSize = 10;

Game::Game() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_initFramerate(&fpsManager_);
  SDL_setFramerate(&fpsManager_, fps);

  graphics_ = std::make_unique<Graphics>();
  tileset_ = std::make_unique<Tileset>("resources/tilesets/Weiholmir XL Full.png", *graphics_,
                                       tileSize, tileSize);

  auto &player = actors_.emplace_back(glm::vec2{1, 1});
  player.addComponent<SpriteComponent>("resources/tilesets/Weiholmir XL Full.png", *graphics_, 92,
                                       tileSize, tileSize, glm::u8vec4{0xFF, 0xFF, 0x00, 0xFF});
  player.addComponent<KeyboardInputComponent>(keyboard_);
}

Game::~Game() {
  IMG_Quit();
  SDL_Quit();
}

void Game::loop() {
  ticks_ = SDL_GetTicks();

  while (isRunning_) {
    processInput();
    update();
    render();

    SDL_framerateDelay(&fpsManager_);
  }
}

void Game::processInput() {
  auto event = SDL_Event{};

  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
    case SDL_QUIT:
      isRunning_ = false;
      break;

    case SDL_KEYDOWN:
      keyboard_.onKeyDown(event.key);
      break;

    case SDL_KEYUP:
      keyboard_.onKeyUp(event.key);
      break;
    }
  }
}

void Game::update() {
  const auto deltaTime = static_cast<float>(SDL_GetTicks() - ticks_) / 1000.0F;
  ticks_ = SDL_GetTicks();

  for (auto &actor : actors_) {
    actor.update(deltaTime);
  }
}

void Game::render() {
  graphics_->prepare();

  for (const auto &actor : actors_) {
    actor.render(*graphics_);
  }

  graphics_->present();
}
} // namespace nsd
