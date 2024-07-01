
# Linux Kernel Module: Kthread Example

This Linux Kernel Module (LKM) demonstrates the usage of kernel threads (kthreads) in a simple example. The module creates two kernel threads that increment separate counters and log their activity to the kernel log.

## Description

This example showcases how to create and manage kernel threads within a Linux Kernel Module. 

- kthread 1 runs every one second
- kthread 2 runs every two seconds.




## Kernel Log Output

The following is a sample output of the kernel log after loading the module and observing the kthread behavior:


![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/a8af8cb0-1f3a-4512-9faa-0b6a81d9b496)



## Installation and Usage

1. **Build the Module**: Compile the kernel module using the following command:
    ```sh
    make
    ```

2. **Insert the Module**: Load the module into the kernel with the command:
    ```sh
    sudo insmod kthread.ko
    ```

3. **Check Kernel Log**: View the kernel log to see the output from the kthreads:
    ```sh
    dmesg | tail
    ```

4. **Remove the Module**: Unload the module from the kernel using:
    ```sh
    sudo rmmod kthread.ko
    ```
 - When removing the module from the kernel, both threads need to be stopped.
 - Use the `kthread_stop` function to stop kthread1 and kthread2.

## Files

- `kthread.c`: The source code of the kernel module.
- `Makefile`: The makefile to build the kernel module.

## Acknowledgements

This example is inspired by various online resources and kernel module development guides.

```
