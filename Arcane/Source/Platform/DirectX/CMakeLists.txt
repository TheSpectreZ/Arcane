cmake_minimum_required(VERSION 3.5)
project(ArcDirectXProject VERSION 1.0.0 LANGUAGES CXX)

add_library(GDirectX SHARED)
add_dependencies(GDirectX Graphics Core)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(GDirectX PRIVATE ${FILE_LIST})		
target_link_libraries(GDirectX PUBLIC Graphics)

target_include_directories(GDirectX PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(GDirectX PRIVATE ARC_DIRECTX_EXPORT=1)

set_target_properties(GDirectX PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET GDirectX PROPERTY FOLDER "Arcane/Platform")