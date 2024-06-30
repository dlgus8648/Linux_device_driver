
# 02_Device Numbers Kernel Module

# 02_01 Insmod
![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/a628118c-a8d1-4553-a622-28000e6cf2ee)

## Description
The "Device Numbers" module is a Linux kernel module that registers a character device and assigns it a major device number. This example demonstrates how to work with device numbers in the kernel.

## Commands Executed
The following commands were used to insert the module and verify its registration:

1. `sudo insmod dev_nr.ko`
   - Inserts the kernel module into the kernel.
2. `cat /proc/devices | grep my_dev_nr`
   - Displays the list of registered devices and filters the output to show the entry for `my_dev_nr`.

## Kernel Log Messages and /proc/devices Output
Below is the explanation of the kernel log messages and the `/proc/devices` output:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ sudo insmod dev_nr.ko
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ cat /proc/devices | grep my_dev_nr
 64 my_dev_nr
```

### Detailed Explanation
1. `sudo insmod dev_nr.ko`
   - This command inserts the kernel module `dev_nr.ko` into the kernel. The module's initialization function is executed, which registers a character device with a specific major device number.
   
2. `cat /proc/devices | grep my_dev_nr`
   - The `/proc/devices` file contains a list of all registered character and block devices in the system, along with their major device numbers. By using `grep my_dev_nr`, we filter the list to find the entry for our device.

### Output Explanation
- `64 my_dev_nr`
  - This line indicates that the device named `my_dev_nr` has been successfully registered with the major device number `64`. The major number uniquely identifies the device driver associated with `my_dev_nr`.


## Conclusion
The above steps and outputs confirm the correct functionality of the "Device Numbers" kernel module. The module successfully registers a character device named `my_dev_nr` with the major device number `64`, and this registration can be verified by examining the `/proc/devices` file.

This exercise helps in understanding how to manage device numbers in Linux kernel modules, providing a foundation for creating and handling custom devices.

---

# 02_02 

![2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/68927307-634e-407a-9fe5-a947a62d4589)
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/8750263e-4988-4760-b5f0-6e2ae64580fe)

## Description
The "Device Numbers" module is a Linux kernel module that registers a character device and assigns it a major device number. This example demonstrates how to create a device file in the `/dev` directory that corresponds to the registered device and how to verify the registration through kernel logs.

## Commands Executed
The following commands were used to create the device file, list its attributes, and check the kernel log messages:

1. `sudo mknod /dev/mydevice c 64 0`
   - Creates a device file named `mydevice` in the `/dev` directory with the major number `64` and minor number `0`.
2. `ls /dev/mydevice -al`
   - Lists the attributes of the `mydevice` file to verify its creation and properties.
3. `dmesg | tail -2`
   - Displays the last two messages from the kernel log buffer to verify the device registration.

## Kernel Log Messages and /dev Directory Output
Below is the explanation of the kernel log messages and the `/dev` directory output:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ ls /dev/mydevice -al
crw-r--r-- 1 root root 64, 0 Jun 30 01:21 /dev/mydevice
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ ^C
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ dmesg | tail -2
[  390.169717] Hello, Kernel!
[  390.169731] dev_nr - registered Device number Major: 64, Minor: 0
```

### Detailed Explanation
1. `ls /dev/mydevice -al`
   - This command lists the details of the `mydevice` file, showing its permissions, owner, group, and major/minor numbers.

2. `dmesg | tail -2`
   - This command displays the last two messages from the kernel log. These messages confirm the registration of the device with the kernel.

### Output Explanation
- `crw-r--r-- 1 root root 64, 0 Jun 30 01:21 /dev/mydevice`
   - `/dev/mydevice`: The name and path of the device file.

- `[90342.480445] Hello, Kernel!`
  - This message is logged by the module during its initialization, indicating that the module has been successfully loaded.

- `[90342.480492] dev_nr - registered Device number Major: 64, Minor: 0`
  - This message confirms that the device `dev_nr` has been registered with the major number `64` and minor number `0`.


## Conclusion
The above steps and outputs confirm the correct functionality of the "Device Numbers" kernel module. The module successfully registers a character device named `my_dev_nr` with the major device number `64`, and this registration can be verified by creating a device file in the `/dev` directory and checking the kernel log messages.

This exercise helps in understanding how to manage device numbers and device files in Linux kernel modules, providing a foundation for creating and handling custom devices.


---

# 02_03


![4](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/d2af0aa5-09c2-4d5f-95fc-b2257999f7b6)
![5](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/e225dd40-8c82-4889-a5a9-70f1ccab8b93)

## Description
The "Device Numbers" module is a Linux kernel module that registers a character device and assigns it a major device number. This example demonstrates how to create a device file in the `/dev` directory that corresponds to the registered device, modify its permissions, and interact with it using a test program.

## Commands Executed
The following commands were used to create the device file, list its attributes, modify its permissions, and check the kernel log messages:

1. `sudo mknod /dev/mydevice c 64 0`
   - Creates a device file named `mydevice` in the `/dev` directory with the major number `64` and minor number `0`.
2. `sudo chmod 666 /dev/mydevice`
   - Changes the permissions of the `mydevice` file to allow read and write access for all users.
3. `./test`
   - Executes the test program to open and close the device file.
4. `dmesg | tail -4`
   - Displays the last four messages from the kernel log buffer to verify the device interaction.

## Kernel Log Messages and /dev Directory Output
Below is the explanation of the kernel log messages and the `/dev` directory output:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ sudo chmod 666 /dev/mydevice
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ ./test
Opening was successful!
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ dmesg | tail -4
[  390.169717] Hello, Kernel!
[  390.169731] dev_nr - registered Device number Major: 64, Minor: 0
[  904.880485] dev_nr - open was called!
[  904.880798] dev_nr - close was called!
```

### Detailed Explanation
1. `sudo chmod 666 /dev/mydevice`
   - This command changes the permissions of the `mydevice` file to `rw-rw-rw-`, allowing read and write access for the owner, group, and others.

2. `./test`
   - This command executes the test program, which attempts to open and close the `mydevice` file. The message `Opening was successful!` indicates that the device file was successfully opened by the test program.

3. `dmesg | tail -4`
   - This command displays the last four messages from the kernel log. These messages confirm the initialization of the module and the interaction with the device file.

### Output Explanation
- `[90342.480445] Hello, Kernel!`
  - This message is logged by the module during its initialization, indicating that the module has been successfully loaded.

- `[90342.480492] dev_nr - registered Device number Major: 64, Minor: 0`
  - This message confirms that the device `dev_nr` has been registered with the major number `64` and minor number `0`.

- `[90542.893823] dev_nr - open was called!`
  - This message is logged when the device file is opened by the test program, indicating that the `open` function of the device driver was called.

- `[90542.894195] dev_nr - close was called!`
  - This message is logged when the device file is closed by the test program, indicating that the `close` function of the device driver was called.



## Conclusion
The above steps and outputs confirm the correct functionality of the "Device Numbers" kernel module. The module successfully registers a character device named `my_dev_nr` with the major device number `64`, and this registration can be verified by creating a device file in the `/dev` directory, modifying its permissions, and interacting with it using a test program.

This exercise helps in understanding how to manage device numbers and device files in Linux kernel modules, providing a foundation for creating and handling custom devices.

---
