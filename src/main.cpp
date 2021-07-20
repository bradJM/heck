#include "game.h"
#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <stdexcept>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  try {
    auto game{nsd::Game{}};
    game.loop();

    return 0;
  } catch (const std::exception &ex) {
    auto message{fmt::format("Heck! had a problem and had to shut down. If you "
                             "need help, please send us the following error message:\n\n{}",
                             ex.what())};

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Heck! Error", message.c_str(), nullptr);

    return 1;
  }
}
