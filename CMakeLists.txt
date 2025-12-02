cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

find_package(PkgConfig REQUIRED)

project(bare_web_kit_gtk C)

pkg_check_modules(GTK REQUIRED IMPORTED_TARGET GLOBAL gtk4)
pkg_check_modules(WebKitGTK REQUIRED IMPORTED_TARGET GLOBAL webkitgtk-6.0)

add_bare_module(bare_web_kit_gtk)

target_sources(
  ${bare_web_kit_gtk}
  PRIVATE
    binding.c
)

target_link_libraries(
  ${bare_web_kit_gtk}
  PUBLIC
    PkgConfig::GTK
    PkgConfig::WebKitGTK
)
