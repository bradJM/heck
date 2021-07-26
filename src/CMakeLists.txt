add_executable(
  heck
  WIN32
  main.cpp
  actor.cpp
  actor_collection.cpp
  actor_factory.cpp
  archetype.cpp
  bitmask.cpp
  bsp_generator.cpp
  game.cpp
  graphics.cpp
  keyboard.cpp
  map.cpp
  #actions/attack_action.cpp
  actions/move_action.cpp
  actions/wait_action.cpp
  components/ai_component.cpp
  #components/attacker_component.cpp
  #components/defender_component.cpp
  components/keyboard_input_component.cpp
  components/sprite_component.cpp
)

set_property(TARGET heck PROPERTY CXX_STANDARD 17)
set_property(TARGET heck PROPERTY CXX_STANDARD_REQUIRED True)
set_property(TARGET heck PROPERTY CXX_EXTENSIONS False)

if (MSVC)
  target_compile_options(heck PRIVATE /W4 /WX)
  target_link_options(heck PRIVATE /WX)
else()
  target_compile_options(heck PRIVATE -Werror -Wall -Wextra -Wunused -Wshadow -Wnon-virtual-dtor -Woverloaded-virtual -pedantic-errors)
endif()

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(
  heck
  PRIVATE
  SDL2::SDL2
  SDL2::SDL2main
  SDL2::SDL2_image
  SDL2::SDL2_gfx
  glm::glm
  libtcod::libtcod
  fmt::fmt
  nlohmann_json::nlohmann_json
)

add_custom_command(
  TARGET heck POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:heck>/resources
)
