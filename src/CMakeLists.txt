add_executable(
  heck
  WIN32
  main.cpp
  actor.cpp
  bitmask.cpp
  game.cpp
  graphics.cpp
  keyboard.cpp
  keyboard_input_component.cpp
  sprite_component.cpp
  tileset.cpp
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
)

add_custom_command(
  TARGET heck POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:heck>/resources
)
