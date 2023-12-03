# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct E:\HDLProjects\axi_stream_array_sum_microblaze\classic_ws\hw_def_design_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source E:\HDLProjects\axi_stream_array_sum_microblaze\classic_ws\hw_def_design_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {hw_def_design_wrapper}\
-hw {E:\HDLProjects\axi_stream_array_sum_microblaze\hw_def_vivado\hw_def_design_wrapper.xsa}\
-out {E:/HDLProjects/axi_stream_array_sum_microblaze/classic_ws}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {hw_def_design_wrapper}
platform generate -quick
bsp reload
bsp reload
platform generate
