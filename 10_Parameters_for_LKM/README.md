# 10_Parameters_for_LKM


### Interpretation

1. **Compilation and Module Loading**
   -  The first command demonstrates the kernel module writing default parameters
   -  (`gpio_nr = 12` and `device_name = testdevice`).

2. **Reloading after Parameter Change**
   - The second command shows the kernel module being loaded with specific parameters
   - (`device_name="dummy"` and `gpio_nr=2`).

### Summary

This project uses a kernel module named my_params.ko. 
This module accepts **two parameters**: `device_name` and `gpio_nr`. 
Each parameter is set by the kernel when the module is initialized.
