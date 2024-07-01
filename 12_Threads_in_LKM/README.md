
# Linux Kernel Module: Kthread Example

This Linux Kernel Module (LKM) demonstrates the usage of kernel threads (kthreads) in a simple example. The module creates two kernel threads that increment separate counters and log their activity to the kernel log.

## Description

This example showcases how to create and manage kernel threads within a Linux Kernel Module. 

- kthread 1 runs every one second
- kthread 2 runs every two seconds.

```markdown
## Kernel Log Output

The following is a sample output of the kernel log after loading the module and observing the kthread behavior:

```bash
[124552.691358] kthread - Thread 1 is executed! Counter val: 0
[124552.691401] kthread - Thread 2 was created and is running now!
[124552.691403] kthread - Both threads are running now!
[124552.691406] kthread - Thread 2 is executed! Counter val: 0
[124553.695772] kthread - Thread 1 is executed! Counter val: 1
[124554.719768] kthread - Thread 1 is executed! Counter val: 2
[124554.719788] kthread - Thread 2 is executed! Counter val: 1
[124555.743780] kthread - Thread 1 is executed! Counter val: 3
[124556.735769] kthread - Thread 2 is executed! Counter val: 2
[124556.767771] kthread - Thread 1 is executed! Counter val: 4
[124558.815794] kthread - Thread 1 is executed! Counter val: 6
[124559.839780] kthread - Thread 1 is executed! Counter val: 7
[124560.767791] kthread - Thread 2 is executed! Counter val: 4
[124560.863794] kthread - Thread 1 is executed! Counter val: 8
[124561.887787] kthread - Thread 1 is executed! Counter val: 9
[124562.783790] kthread - Thread 2 is executed! Counter val: 5
[124562.911772] kthread - Thread 1 is executed! Counter val: 10
[124563.935790] kthread - Thread 1 is executed! Counter val: 11
[124564.799786] kthread - Thread 2 is executed! Counter val: 6
[124564.959774] kthread - Thread 1 is executed! Counter val: 12
```

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
