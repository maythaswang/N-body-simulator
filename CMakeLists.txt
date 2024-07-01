cmake_minimum_required(VERSION 3.16)

project(N_body_simulator)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CSS_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/result")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)

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

set(PROJECT_SOURCES
    src/main.cpp
    src/DisplaySystem/WindowFactory/WindowFactory.cpp
    src/DisplaySystem/Camera/Camera.cpp
    src/CallbackManager/CallbackManager.cpp
    src/ParticleSystem/Particle/Particle.cpp
    src/ProgramInit/ProgramInit.cpp
    src/Shader/Shader.cpp
    src/Polygon/SamplePolygon/SamplePolygon.cpp
    src/ParticleSystem/Simulator/Simulator.cpp
)

set(INCLUDE_DIRS
    include/
    src/include/
    src/DisplaySystem/
    src/DisplaySystem/WindowFactory/
    src/DisplaySystem/Camera/
    src/ParticleSystem/Particle/
    src/CallbackManager/
    src/ProgramInit/
    src/Shader/
    src/Polygon/SamplePolygon/
    src/ParticleSystem/Simulator/
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw glm glad)