#include "game.h"
#include "graphics.h"
#include "keyboard.h"
#include "map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

namespace nsd {
constexpr auto fps{60};
constexpr auto mapWidth{50};
constexpr auto mapHeight{30};

Game::Game() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_initFramerate(&fpsManager_);
  SDL_setFramerate(&fpsManager_, fps);

  graphics_ = std::make_unique<Graphics>();
  map_ = std::make_unique<Map>(mapWidth, mapHeight);
}

Game::~Game() {
  IMG_Quit();
  SDL_Quit();
}

void Game::loop() {
  while (isRunning_) {
    processInput();
    turn();
    render();
  }
}

void Game::processInput() {
  auto event{SDL_Event{}};

  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
    case SDL_QUIT:
      isRunning_ = false;
      break;

    case SDL_KEYDOWN:
      Keyboard::getInstance().onKeyDown(event.key);
      break;

    case SDL_KEYUP:
      Keyboard::getInstance().onKeyUp(event.key);
      break;
    }
  }
}

void Game::turn() {
  map_->turn();

  // temporary!
  SDL_Delay(10);
}

void Game::render() {
  graphics_->prepare();

  map_->render(*graphics_);

  graphics_->present();
}
} // namespace nsd
