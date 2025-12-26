# Heterogeneous SoC Median Filter Implementation

This repository contains the implementation of a 5x5 Median Filter across heterogeneous computing platforms: CPU (Scalar & Vectorized), GPU (OpenCL), and FPGA (Vitis HLS). The project demonstrates performance optimization techniques including SIMD vectorization, memory tiling, and hardware pipelining.

## Project Structure

The repository is organized into two main components:

```text
heterogen_soc_hf/
├── cpu_opencl/             # Tasks 3.1 - 3.3: Host Application
│   ├── src/                # C++ source code and OpenCL kernels
│   ├── include/            # Header files
│   └── CMakeLists.txt      # Build configuration (Universal)
│
├── fpga_hls/               # Task 3.4: Hardware Acceleration
│   └── src/                # Synthesizable C++ code for Vitis HLS
│
└── docs/                   # Documentation and reports
```
## Prerequisites

To build and run the projects, you will need the following tools and libraries:

* **Compiler:** `g++` (GCC) or `clang` supporting C++17.
* **Build System:** CMake (3.10+) and Make.
* **OpenCL:** OpenCL headers and ICD loader (e.g., `ocl-icd-opencl-dev`).
* **Libraries:**
    * **OpenMP** (for multi-threading support).
    * **DevIL** (Image Library) development headers (`libopenil-dev`).
    * **LibSndFile** development headers (`libsndfile1-dev`).
* **FPGA Tools (Optional):** Xilinx Vitis HLS and Vivado (2020.2 or newer) for synthesis.

## Part 1: CPU & OpenCL Implementation

The `cpu_opencl` folder contains the host application that runs the scalar reference, vectorized CPU implementation (AVX/NEON), and the OpenCL GPU kernels.

### Building on Linux / WSL

1.  Navigate to the directory:
    ```bash
    cd cpu_opencl
    ```
2.  Create a build directory:
    ```bash
    mkdir build && cd build
    ```
3.  Configure with CMake:
    ```bash
    cmake ..
    ```
    *Note: CMake will automatically detect if you are cross-compiling (e.g., for ARM64) and adjust flags accordingly.*

4.  Compile:
    ```bash
    make
    ```
### Running the Application

After building, the executable `host_app` (or `median_filter` depending on your CMake setup) will be generated in the build directory. Ensure the input images are available relative to the execution path.

```bash
./host_app
```

## Part 2: FPGA HLS Implementation

The `fpga_hls` folder contains the C++ source code for the streaming median filter hardware kernel.

### Source Code Location
* **Hardware Kernel:** `fpga_hls/src/median2d_hw.cpp`
* **Testbench:** `fpga_hls/src/tb_median2d.cpp`
* **Headers:** `fpga_hls/src/types.h`

### Building the Project (Vitis HLS)

Since this repository contains only the source files, you must create a new project to synthesize the IP.

1.  **Launch Vitis HLS.**
2.  **Create a New Project:**
    * Click "Create New Project" and specify the project name/location.
3.  **Add Source Files:**
    * Under **Design Files**, add `fpga_hls/src/median2d_hw.cpp`.
    * Set the **Top Function** to `median2d_hw`.
    * Under **Test Bench Files**, add `fpga_hls/src/tb_median2d.cpp`.
4.  **Solution Configuration:**
    * Select your target FPGA part (e.g., Zynq UltraScale+ or equivalent).
    * Set the clock period (e.g., 10ns for 100MHz).
    * Finish the setup.
5.  **Run Synthesis:**
    * Click the **C Synthesis** button (green play icon) to generate the RTL.
