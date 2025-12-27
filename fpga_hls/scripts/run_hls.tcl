# 1. Set up the project
# 'proj_median' is the output folder name. -reset overwrites it if it exists.
open_project -reset proj_median

# 2. Set the Top-Level Function
set_top median2d_hw

# 3. Add Source Files (Synthesizable)
add_files src/median.cpp
add_files src/types.h

# 4. Add Testbench Files
# The -cflags is optional but good for include paths if needed
add_files -tb tb/median_tb.cpp -cflags "-Isrc"

# 5. Create the Solution
open_solution "solution1" -flow_target vivado

# 6. Define Part and Clock
# Replace this with your specific FPGA part
set_part {xc7k70tfbg484-1}
create_clock -period 5 -name default

# 7. Directives (Optional)
# If you have a directives.tcl, source it here:
# source "./scripts/directives.tcl"

# 8. Execution Steps (Uncomment what you need)
# Run C Simulation
csim_design

# Run Synthesis
csynth_design

# Run C/RTL Co-simulation
cosim_design

# Export the IP
export_design -format ip_catalog

# Exit
exit