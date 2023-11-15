cmake_minimum_required(VERSION 3.10)
project(cellular_automaton)

# Set Clang as the default compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Set the executable name
set(EXECUTABLE_NAME simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Werror -g")

# Use GLOB to get all .cpp files in src directory
file(GLOB SOURCES src/*.cpp)

# Add the INIreader module
file(GLOB INIREADER_SOURCES INIreader/*.cpp INIreader/*.c)

# Executable
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${INIREADER_SOURCES})

# Include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/INIreader
    ${CMAKE_SOURCE_DIR}/3rdparty/cxxopts/include  # Include cxxopts directory
)

# External libraries (assuming these are needed)
find_package(OpenGL REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${OPENGL_LIBRARIES} glut GLU GL Xext X11 m)
