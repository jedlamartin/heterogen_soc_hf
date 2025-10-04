cmake_minimum_required(VERSION 3.16)
project(heterogen_soc LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries (example, modify as needed)
# target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)