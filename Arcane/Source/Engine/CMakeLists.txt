cmake_minimum_required(VERSION 3.5)
project(ArcEngineProject VERSION 1.0.0 LANGUAGES CXX)

add_library(Engine SHARED)
add_dependencies(Engine Core Graphics ${GraphicsImpl})
add_natvis(Engine)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(Engine PRIVATE ${FILE_LIST})		
target_link_libraries(Engine PUBLIC Core Scene Graphics ${GraphicsImpl})

target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(Engine PRIVATE ARC_ENGINE_EXPORT=1)

set_target_properties(Engine PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET Engine PROPERTY FOLDER "Arcane")