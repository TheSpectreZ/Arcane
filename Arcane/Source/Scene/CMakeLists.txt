cmake_minimum_required(VERSION 3.5)
project(ArcSceneProject VERSION 1.0.0 LANGUAGES CXX)

add_library(Scene SHARED)
add_dependencies(Scene Core)
add_natvis(Scene)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(Scene PRIVATE ${FILE_LIST})		
target_link_libraries(Scene PUBLIC Core)

target_include_directories(Scene PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(Scene PRIVATE ARC_SCENE_EXPORT=1)

set_target_properties(Scene PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET Scene PROPERTY FOLDER "Arcane")
