# 10_Parameters_for_LKM


### Interpretation

**1. Compilation and Module Loading**

![제목 없음](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6ea9f9af-9d7c-443a-8c68-8625ff994bda)

   -  The first command demonstrates the kernel module writing default parameters
   -  (`gpio_nr = 12` and `device_name = testdevice`).







**2. Reloading after Parameter Change**

![제목 없음2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/170e117a-bd97-4476-89b1-a8dda6afa4a2)

   - The second command shows the kernel module being loaded with specific parameters
   - (`device_name="dummy"` and `gpio_nr=2`).



### Summary
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/0102f8cf-0888-486f-b682-8af0887306d3)

This project uses a kernel module named my_params.ko. 
- This module accepts **two parameters**: `device_name` and `gpio_nr`. 
- Each parameter is set by the kernel when the module is initialized.
