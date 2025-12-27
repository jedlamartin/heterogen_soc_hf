# scripts/run_vivado.tcl

# --- Configuration ---
set project_name "hdmi_median_proj"
set device_part "xc7k70tfbg676-1" 
# Point to where HLS generated the IP (adjust if your HLS output path differs)
set hls_ip_path "./proj_median/solution1/impl/ip"

# 1. Create the Project
puts "Creating Vivado Project..."
create_project -force $project_name ./vivado_project -part $device_part

# 2. Add RTL and Netlist Sources
#    Vivado automatically pairs .v wrappers with .edn netlists
add_files -norecurse {
    ./rtl/hdmi_top.v
    ./rtl/hdmi_rx.v
    ./rtl/hdmi_rx.edn
    ./rtl/hdmi_tx.v
    ./rtl/hdmi_tx.edn
}

# 3. Add Constraints
add_files -fileset constrs_1 -norecurse {
    ./constraints/hdmi_top.xdc
    ./constraints/chipscope.xdc
}

# 4. Set Up HLS IP Repository
puts "Setting up IP Repo..."
set_property ip_repo_paths $hls_ip_path [current_project]
update_ip_catalog

# 5. Generate the HLS IP Instance
puts "Creating HLS IP Instance..."
create_ip -name median2d_hw -vendor xilinx.com -library hls -module_name median2d_hw_0

# 6. Generate IP Output Products (Synthesis files for the IP)
generate_target all [get_ips median2d_hw_0]
create_ip_run [get_ips median2d_hw_0]

# 7. Set Top Module
set_property top hdmi_top [current_fileset]

# 8. Finalize
update_compile_order -fileset sources_1

puts "---------------------------------------------"
puts " Project Created Successfully!"
puts " To open the GUI, run: start_gui"
puts " Or open manually: vivado_project/$project_name.xpr"

puts "---------------------------------------------"
