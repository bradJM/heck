cmake_minimum_required(VERSION 3.20)
project(heck_proj VERSION 1.0 LANGUAGES C CXX)

add_subdirectory(src)

add_custom_target(
  copy-compile-commands ALL
  ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_LIST_DIR}
)
