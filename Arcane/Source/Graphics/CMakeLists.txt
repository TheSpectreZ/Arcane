cmake_minimum_required(VERSION 3.5)
project(ArcGraphicsProject VERSION 1.0.0 LANGUAGES CXX)

add_library(Graphics SHARED)
add_dependencies(Graphics Core)
add_natvis(Graphics)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(Graphics PRIVATE ${FILE_LIST})		
target_link_libraries(Graphics PUBLIC Core)

target_include_directories(Graphics PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(Graphics PRIVATE ARC_GRAPHICS_EXPORT=1)

set_target_properties(Graphics PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET Graphics PROPERTY FOLDER "Arcane")