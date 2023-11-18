cmake_minimum_required(VERSION 3.10)
project(cellular_automaton)



# Prefer Clang as the default C++ compiler
if(NOT CMAKE_CXX_COMPILER AND EXISTS /usr/bin/clang++)
    set(CMAKE_CXX_COMPILER "clang++")
endif()
if(NOT CMAKE_C_COMPILER AND EXISTS /usr/bin/clang)
    set(CMAKE_C_COMPILER "clang")
endif()

# If clang was not found, set GNU g++ as default compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Set the executable name
set(EXECUTABLE_NAME cellular_automaton)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Werror -g")

# Use GLOB to get all .cpp files in src directory
set(SOURCES src/CellularAutomaton.cpp src/Coordinates.cpp src/Grid.cpp src/Polluter.cpp src/Polluters.cpp src/Statistics.cpp src/WindField.cpp src/main.cpp)

if(OpenGL_FOUND)
    list(APPEND SOURCES src/render.cpp)
endif()

# Add the INIreader module
file(GLOB INIREADER_SOURCES INIreader/*.cpp INIreader/*.c)

# Executable
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${INIREADER_SOURCES})

# Include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/3rdparty/cxxopts/include  # Include cxxopts directory
)

# External libraries (assuming these are needed)
if(OpenGL_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${OPENGL_LIBRARIES} glut GLU GL Xext X11 m)
else()
    message(WARNING "OpenGL not found. The executable will be built without OpenGL support.")
endif()
