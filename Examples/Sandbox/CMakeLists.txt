cmake_minimum_required(VERSION 3.5)
project(ArcSanboxProject VERSION 1.0.0 LANGUAGES CXX)

add_executable(Sandbox WIN32)
add_dependencies(Sandbox Application)			
add_natvis(Sandbox)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(Sandbox PRIVATE ${FILE_LIST})		

target_link_libraries(Sandbox PRIVATE Application)

set_target_properties(Sandbox PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET Sandbox PROPERTY FOLDER "Examples")