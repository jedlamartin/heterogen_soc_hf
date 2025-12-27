cmake_minimum_required(VERSION 3.10)
project(HeterogeneousSoc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Dependencies ---
find_package(OpenMP REQUIRED)
find_package(OpenCL REQUIRED)

# Use CMake's native finder for DevIL instead of PkgConfig
find_package(DevIL REQUIRED)

# --- 2. Compiler Flags ---
add_compile_options(-Wall -Wextra -O3 -ggdb)

if(NOT CMAKE_CROSSCOMPILING)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_NATIVE)
    if(COMPILER_SUPPORTS_NATIVE)
        add_compile_options(-march=native)
    endif()
endif()

# --- 3. Source Files ---
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- 4. Define Executable ---
add_executable(host_app ${SOURCES})

# --- 5. Linking ---
target_include_directories(host_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCL_INCLUDE_DIRS}
    ${DEVIL_INCLUDE_DIR}
)

target_link_libraries(host_app PRIVATE
    OpenCL::OpenCL
    OpenMP::OpenMP_CXX
    ${IL_LIBRARIES}    # Main DevIL library
    ${ILU_LIBRARIES}   # Utility library
)

# --- 6. Kernel Copying ---
file(GLOB KERNEL_FILES "src/*.cl")
foreach(KERNEL_FILE ${KERNEL_FILES})
    get_filename_component(FILENAME ${KERNEL_FILE} NAME)
    add_custom_command(
        TARGET host_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${KERNEL_FILE}
        $<TARGET_FILE_DIR:host_app>/${FILENAME}
    )
endforeach()
