# heterogen_soc_hf

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
│   ├── src/                # Synthesizable HLS Source (median.cpp, types.h)
│   ├── tb/                 # HLS Testbench (median_tb.cpp)
│   ├── rtl/                # RTL Integration (hdmi_top.v, .edn netlists, wrappers)
│   ├── xdc/                # Physical Constraints (hdmi_top.xdc, chipscope.xdc)
│   └── scripts/            # Build automation (run_hls.tcl, run_vivado.tcl)
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

The `fpga_hls` folder contains the complete hardware design flow, including HLS C++ source code, testbenches, and Vivado integration scripts for the HDMI-based video pipeline.

### Source Code Location
* **Hardware Kernel:** `fpga_hls/src/median.cpp`
* **Testbench:** `fpga_hls/tb/median_tb.cpp`
* **Headers:** `fpga_hls/src/types.h`

### Building the Project (Scripted Flow)

This repository uses Tcl scripts to automate the project recreation and build process. This ensures reproducibility without relying on absolute paths or large project files.

**1. Run High-Level Synthesis (HLS)**
This step runs C-simulation, synthesizes the C++ code into RTL, and exports the IP core.
```bash
cd fpga_hls
vitis-run --mode hls --tcl scripts/run_hls.tcl
```
*Output:* The generated IP will be located in `fpga_hls/proj_median/solution1/impl/ip`.

**2. Run Vivado Integration**
This step creates the Vivado project, imports the HLS IP, links the RTL/Netlists, and applies constraints.
```bash
# From the fpga_hls directory
vivado -mode batch -source scripts/run_vivado.tcl
```
*Output:* A fully configured Vivado project will be created in `fpga_hls/vivado_project`.

**3. Open the Project (Optional)**
To view the design or generate the bitstream manually:
```bash
vivado vivado_project/hdmi_median_proj.xpr
```
