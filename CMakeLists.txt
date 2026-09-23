cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

find_package(PkgConfig REQUIRED)

project(bare_web_kit_gtk C)

pkg_check_modules(GTK REQUIRED IMPORTED_TARGET GLOBAL gtk4>=4.6)

# The version the prebuilds are built against.
target_compile_definitions(
  PkgConfig::GTK
  INTERFACE
    GDK_VERSION_MIN_REQUIRED=GDK_VERSION_4_6
    GDK_VERSION_MAX_ALLOWED=GDK_VERSION_4_6
)

# The release that introduced the 6.0 API. WebKitGTK has no equivalent of GDK's
# version macros, so the floor can only be enforced here.
pkg_check_modules(WebKitGTK REQUIRED IMPORTED_TARGET GLOBAL webkitgtk-6.0>=2.40)

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
