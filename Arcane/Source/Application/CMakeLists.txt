cmake_minimum_required(VERSION 3.5)
project(ArcApplicationProject VERSION 1.0.0 LANGUAGES CXX)

add_library(Application SHARED)
add_dependencies(Application Engine Core)
add_natvis(Application)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(Application PRIVATE ${FILE_LIST})		
target_link_libraries(Application PUBLIC Engine)

target_include_directories(Application PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(Application PRIVATE ARC_APPLICATION_EXPORT=1)

set_target_properties(Application PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET Application PROPERTY FOLDER "Arcane")