# 09_High_Resolution_Timer

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/ac3e40f3-c113-40a6-b3d6-4c68233eda78)


### Interpretation

1. **`[   73.506131] Hello, Kernel!`**
   - **Timestamp**: `73.506131 seconds` after the kernel has booted.
   - **Message**: "Hello, Kernel!" - This is a informational message from the kernel.

2. **`[   73.606154] start_t - now_t = 100`**
   - **Timestamp**: `73.606154 seconds` after the kernel has booted.
   - **Message**: The difference between two timestamps `start_t` and `now_t` is `100`.
   - **Explanation**: 
     - The difference `start_t - now_t` equals `100 milliseconds`.
     - Calculation: `73.606154 - 73.506131 = 0.100023 seconds = 100 milliseconds`.

### Summary

The kernel messages indicate that at approximately `73.506131 seconds` after boot, the kernel printed "Hello, Kernel!". Subsequently, at `73.606154 seconds` after boot, it calculated and printed the difference between two timestamps (`start_t` and `now_t`), which was `100 milliseconds`. 
