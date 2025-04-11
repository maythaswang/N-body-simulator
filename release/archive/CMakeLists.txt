# IF SOME THINGS ARE NOT WORKING CORRECTLY, TRY REPLACE CMakeLists.txt in the root dir with this one.

cmake_minimum_required(VERSION 3.16)

project(N_body_simulator)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CSS_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/result")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "UNKNOWN BUILD TYPE. DEFAULTING TO RELEASE")
endif()

# Release build
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(GLFW_BUILD_DOCS FALSE)
    add_definitions(-DRELEASE_BUILD)
    message(STATUS "SELECTED RELEASE BUILD")

# Debug build
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -pedantic")
    set(GLFW_BUILD_DOCS TRUE)
    add_definitions(-DDEBUG_BUILD)
    message(STATUS "SELECTED DEBUG BUILD")

else()
    message(STATUS "UNKNOWN BUILD TYPE")
endif()

# Set fetch content directory
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/packages")
set(FETCHCONTENT_QUIET FALSE)
message(STATUS "FETCHING REQUIRED PACKAGES")

# glfw
set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_PROGRESS TRUE)

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG 1.0.0
    GIT_PROGRESS TRUE)

# glad
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad/
    GIT_TAG v0.1.36
    GIT_PROGRESS TRUE
)

# Fetch Dependencies
FetchContent_MakeAvailable(glfw glm glad)

set(IMGUI_DIR external_dependencies/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/src/imgui_draw.cpp 
    ${IMGUI_DIR}/src/imgui_impl_glfw.cpp 
    ${IMGUI_DIR}/src/imgui_impl_opengl3.cpp 
    ${IMGUI_DIR}/src/imgui_tables.cpp 
    ${IMGUI_DIR}/src/imgui_widgets.cpp 
    ${IMGUI_DIR}/src/imgui.cpp
)

set(PROJECT_SOURCES
    src/main.cpp
    src/DisplaySystem/WindowFactory/WindowFactory.cpp
    src/DisplaySystem/Camera/Camera.cpp
    src/CallbackManager/CallbackManager.cpp
    src/ProgramInit/ProgramInit.cpp
    src/Shader/Shader.cpp
    src/ParticleSystem/Simulator/Simulator.cpp
    src/SetupSystem/ParticleBuilder/ParticleBuilder.cpp
    src/Renderer/Renderer.cpp
    src/ParticleSystem/ParticleParticleCPU/ParticleParticleCPU.cpp
    src/ParticleSystem/ParticleParticleGPU/ParticleParticleGPU.cpp
    src/SetupSystem/InputParser/InputParser.cpp
    src/SetupSystem/DefaultTestLoader/DefaultTestLoader.cpp
    src/Mesh/MeshBuilder.cpp
    src/Bloom/Bloom.cpp
    src/GUI/GUI.cpp
    src/InputProcessor/InputProcessor.cpp
)

set(INCLUDE_DIRS
    include/
    ${IMGUI_DIR}/headers/
    src/
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw glm glad)