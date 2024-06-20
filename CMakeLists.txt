cmake_minimum_required(VERSION 3.16)

project(simple_ray_tracer)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CSS_STANDARD_REQUIRED ON)

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

# glew
FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
    GIT_TAG glew-cmake-2.2.0
    GIT_PROGRESS TRUE
    )

# Fetch Dependencies
FetchContent_MakeAvailable(glfw glm glew)

set(PROJECT_SOURCES
    src/main.cpp
    src/display/display.cpp
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/display/
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_dependencies(${PROJECT_NAME} glfw glm libglew_shared)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw glm libglew_shared)
