# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: E:\HDLProjects\axi_stream_array_sum_microblaze\classic_ws\main_app_system\_ide\scripts\systemdebugger_main_app_system_1_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source E:\HDLProjects\axi_stream_array_sum_microblaze\classic_ws\main_app_system\_ide\scripts\systemdebugger_main_app_system_1_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent Basys3 210183ACAC51A" && level==0 && jtag_device_ctx=="jsn-Basys3-210183ACAC51A-0362d093-0"}
fpga -file E:/HDLProjects/axi_stream_array_sum_microblaze/classic_ws/main_app/_ide/bitstream/download.bit
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw E:/HDLProjects/axi_stream_array_sum_microblaze/classic_ws/hw_def_design_wrapper/export/hw_def_design_wrapper/hw/hw_def_design_wrapper.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow E:/HDLProjects/axi_stream_array_sum_microblaze/classic_ws/main_app/Debug/main_app.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
