cmake_minimum_required(VERSION 3.5)
project(ArcVulkanProject VERSION 1.0.0 LANGUAGES CXX)

add_library(GVulkan SHARED)
add_dependencies(GVulkan Graphics Core)

file(GLOB_RECURSE FILE_LIST "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.h")
target_sources(GVulkan PRIVATE ${FILE_LIST})		
target_link_libraries(GVulkan PUBLIC Graphics)

target_include_directories(GVulkan PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(GVulkan PRIVATE ARC_VULKAN_EXPORT=1)

set_target_properties(GVulkan PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_property(TARGET GVulkan PROPERTY FOLDER "Arcane/Platform")