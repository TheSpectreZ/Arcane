cmake_minimum_required(VERSION 3.5)
project(ARCANE VERSION 1.0.0 LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

message(STATUS "BUILD SYSTEM: ${CMAKE_SYSTEM}")
message(STATUS "BUID SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "BUID SYSTEM PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(OS_WINDOW ON)
    message(STATUS "OPERATING SYSTEM: Windows")
    add_definitions(-DPLATFORM_WINDOWS=1)
else()
    message(FATAL_ERROR "OS Not Supported! ${CMAKE_SYSTEM_NAME}")
endif()

set(CMAKE_DEBUG_POSTFIX "d")

set(ARC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(ARC_BIN "${ARC_ROOT}/Binaries")

set(ARC_DEP "${ARC_ROOT}/Arcane/Dependencies")
set(ARC_SRC "${ARC_ROOT}/Arcane/Source")
set(ARC_EXP "${ARC_ROOT}/Examples")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(USE_MSVC_DYNAMIC_CRT ON CACHE BOOL "Use dynamic CRT (/MD or /MDd) on VS")

if(USE_MSVC_DYNAMIC_CRT AND MSVC)
    set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif()

set(USE_VS_MULTIPROCESS ON CACHE BOOL "Use MultiProcessor compiling on VS")
		
if(USE_VS_MULTIPROCESS AND MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /Zc:__cplusplus")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /bigobj")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LARGEADDRESSAWARE")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ARC_BIN}/ReleaseWithDebug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ARC_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ARC_BIN})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ARC_BIN}/Release/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ARC_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ARC_BIN})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ARC_BIN}/Debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ARC_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ARC_BIN})

include_directories("${ARC_DEP}")
include_directories("${ARC_SRC}")

add_compile_options(/wd4251)

set(USE_VULKAN OFF CACHE BOOL "Use Vulkan Graphics API")
set(USE_D3D12  OFF CACHE BOOL "Use DirectX Graphics API")
set(USE_OPENGL ON CACHE BOOL "Use OpenGL Graphics API")

list(APPEND Dependencies "")

if(USE_VULKAN)
    add_definitions(-DGRAPHICS_VULKAN=1)
    list(APPEND Arcane "${ARC_SRC}/Platform/Vulkan")
    list(APPEND GraphicsImpl "GVulkan")
endif()

if(USE_D3D12)
    add_definitions(-DGRAPHICS_DIRECTX=1)
    list(APPEND Arcane "${ARC_SRC}/Platform/DirectX")
    list(APPEND GraphicsImpl "GDirectX")
endif()

if(USE_OPENGL)
    add_definitions(-DGRAPHICS_OPENGL=1)
    list(APPEND Arcane "${ARC_SRC}/Platform/OpenGL")
    list(APPEND GraphicsImpl "GOpenGL")
endif()

list(APPEND Arcane 
        "${ARC_SRC}/Core"
        "${ARC_SRC}/Scene"
        "${ARC_SRC}/Graphics"
        "${ARC_SRC}/Engine"
        "${ARC_SRC}/Application"
    )

list(APPEND Examples 
        "${ARC_EXP}/Sandbox"
    )

file(GLOB NATVIS_FILES "${ARC_ROOT}/natvis/*.natvis")
message(STATUS "${NATVIS_FILES}")

message(STATUS "Graphics Implementation: ${GraphicsImpl}")

function(add_natvis target_name)
    target_sources(${target_name} PRIVATE ${NATVIS_FILES})
endfunction(add_natvis target_name)

function(add_executable target_name)	
	_add_executable(${target_name} ${ARGN})	
    set_property(TARGET ${target_name} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${ARC_BIN}")	
endfunction(add_executable target_name)

foreach(subdir ${Dependencies})
    message(STATUS "Adding Dependency Project: ${subdir}")
    add_subdirectory(${subdir})
endforeach()

foreach(subdir ${Arcane})
    message(STATUS "Adding Arcane Project: ${subdir}")
    add_subdirectory(${subdir})
endforeach()

foreach(subdir ${Examples})
    message(STATUS "Adding Example Project: ${subdir}")
    add_subdirectory(${subdir})
endforeach()