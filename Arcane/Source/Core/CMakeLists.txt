cmake_minimum_required(VERSION 3.5)
project(ArcCoreProject VERSION 1.0.0 LANGUAGES CXX)

add_library(Core SHARED)
add_natvis(Core)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(Core PRIVATE ${FILE_LIST})		

target_include_directories(Core PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(Core PRIVATE ARC_CORE_EXPORT=1)
target_link_libraries(Core PRIVATE gameinput.lib)

set_target_properties(Core PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET Core PROPERTY FOLDER "Arcane")
