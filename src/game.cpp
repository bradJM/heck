#include "game.h"
#include "actions/action.h"
#include "bsp_generator.h"
#include "components/ai_component.h"
#include "components/keyboard_input_component.h"
#include "components/sprite_component.h"
#include "components/transform_component.h"
#include "graphics.h"
#include "map.h"
#include "tileset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>

namespace nsd {
constexpr auto fps{60};
constexpr auto atlasPath{"resources/tilesets/Weiholmir XL Full.png"};
constexpr auto atlasElementWidth{10};
constexpr auto atlasElementHeight{10};
constexpr auto mapWidth{80};
constexpr auto mapHeight{50};

Game::Game() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_initFramerate(&fpsManager_);
  SDL_setFramerate(&fpsManager_, fps);

  graphics_ = std::make_unique<Graphics>();
  atlas_ = std::make_unique<Atlas>(atlasPath, *graphics_, atlasElementWidth, atlasElementHeight);
  map_ = std::make_unique<Map>(mapWidth, mapHeight, std::make_unique<Tileset>(atlas_.get()));

  auto generator{BspGenerator{map_.get()}};
  generator.generate();

  auto &player{actors_.emplace_back(std::make_unique<Actor>())};
  player->addComponent<TransformComponent>(glm::ivec2{mapWidth / 2, mapHeight / 2});
  player->addComponent<SpriteComponent>(atlas_.get(), 92, glm::u8vec4{0xFF, 0xFF, 0x00, 0xFF});
  player->addComponent<KeyboardInputComponent>(&keyboard_);

  auto &enemy{actors_.emplace_back(std::make_unique<Actor>())};
  enemy->addComponent<TransformComponent>(glm::ivec2{(mapWidth / 2) + 5, mapHeight / 2});
  enemy->addComponent<SpriteComponent>(atlas_.get(), 13, glm::u8vec4{0xFF});
  enemy->addComponent<AiComponent>();
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
      keyboard_.onKeyDown(event.key);
      break;

    case SDL_KEYUP:
      keyboard_.onKeyUp(event.key);
      break;
    }
  }
}

void Game::turn() {
  if (actors_.empty()) {
    return;
  }

  auto action{actors_[currentActor_]->turn()};

  // We're still waiting for this actor to produce an action, so don't advance.
  if (action == nullptr) {
    return;
  }

  while (true) {
    auto result{action->perform()};

    // The action failed, so this actor should get another chance to act.
    if (!result.succeeded) {
      return;
    }

    // We've exhausted alternative actions and the final one succeeded. We're done!
    if (result.alternative == nullptr) {
      break;
    }

    action.swap(result.alternative);
  }

  currentActor_ = (currentActor_ + 1) % actors_.size();

  // temporary!
  SDL_Delay(150);
}

void Game::render() {
  graphics_->prepare();

  map_->render(*graphics_);

  for (const auto &actor : actors_) {
    actor->render(*graphics_);
  }

  graphics_->present();
}
} // namespace nsd
