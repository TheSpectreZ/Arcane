cmake_minimum_required(VERSION 3.5)
project(ArcOpenGLProject VERSION 1.0.0 LANGUAGES CXX)

add_library(GOpenGL SHARED)
add_dependencies(GOpenGL Graphics Core)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(GOpenGL PRIVATE ${FILE_LIST})		
target_link_libraries(GOpenGL PUBLIC Graphics PRIVATE "opengl32.lib")

target_include_directories(GOpenGL PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(GOpenGL PRIVATE ARC_OPENGL_EXPORT=1)

set_target_properties(GOpenGL PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET GOpenGL PROPERTY FOLDER "Arcane/Platform")