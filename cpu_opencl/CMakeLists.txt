cmake_minimum_required(VERSION 3.10)

# Project setup
project(HeterogeneousSoc CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Dependencies ---

# OpenMP (Used in both Makefiles)
find_package(OpenMP REQUIRED)

# OpenCL (Used in AMD Makefile, likely needed for ARM too if code is shared)
find_package(OpenCL REQUIRED)

# PkgConfig is useful for finding linux libraries like libsndfile/DevIL
find_package(PkgConfig REQUIRED)

# Find DevIL (Image Library)
pkg_check_modules(IL REQUIRED IL)   # Looks for libIL
pkg_check_modules(ILU REQUIRED ILU) # Looks for libILU

# Find LibSndFile
pkg_check_modules(SNDFILE REQUIRED sndfile)

# --- 2. Compiler Flags ---

# Common flags from your Makefiles: -Wall -Wextra -O3 -ggdb
add_compile_options(-Wall -Wextra -O3 -ggdb)

# Handle -march=native
# We only want this for the AMD/Host container. 
# If CMAKE_SYSTEM_PROCESSOR matches the host, or if explicitly requested.
if(NOT CMAKE_CROSSCOMPILING)
    # Check if the compiler supports native tuning
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_NATIVE)
    if(COMPILER_SUPPORTS_NATIVE)
        add_compile_options(-march=native)
    endif()
endif()

# --- 3. Source Files ---

# Automatically find all sources in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- 4. Define Executable ---

# You can name this whatever you want. 
# Your makefiles used "median_img_ocl" and "fir_img_vec".
add_executable(host_app ${SOURCES})

# --- 5. Linking ---

# Include directories
target_include_directories(host_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCL_INCLUDE_DIRS}
    ${IL_INCLUDE_DIRS}
    ${SNDFILE_INCLUDE_DIRS}
)

# Link Libraries
target_link_libraries(host_app PRIVATE
    OpenCL::OpenCL
    OpenMP::OpenMP_CXX
    ${IL_LIBRARIES}
    ${ILU_LIBRARIES}
    ${SNDFILE_LIBRARIES}
    # Note: ILUT was in your makefile (-lILUT), add it here if strictly needed:
    # ${ILUT_LIBRARIES} 
)

# --- 6. Kernel Copying (For OpenCL) ---
# Copies .cl files to the build folder so the executable can find them
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