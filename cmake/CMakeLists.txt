cmake_minimum_required(VERSION 3.23)

project("RevEngJam Template" LANGUAGES CXX)

add_library(template MODULE)

file(GLOB_RECURSE template_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

target_sources(template PRIVATE ${template_SOURCES})
target_compile_definitions(template PRIVATE $<$<CONFIG:DEBUG>:DEBUG>)
target_precompile_headers(template PRIVATE src/stdafx.hpp)

set_target_properties(template PROPERTIES LINK_FLAGS "/INCREMENTAL:NO /LARGEADDRESSAWARE")
