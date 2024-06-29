# ioctl_example Module

## 1. Module Loading and Initialization Message:

After initializing the module, the kernel prints the message "Hello, Kernel!" to indicate that the initialization was successful.  
The module indicates that the registered device number has a `Major number of 64` and a `Minor number of 0.`

## 2. Device Node Creation:

A device node named `/dev/dummy` has been created with `Major number 64` and `Minor number 0`.  
This node provides an interface to interact with the `ioctl_example` module.

## 3. User Space Program Execution and Result Verification:

The `./test` program executed in user space interacts with the `ioctl_example` module.  
The first message prints the default response of 42.  
The second message indicates that the response has been updated to 123.  
A message indicating that the device has been successfully opened is displayed.

## 4. Kernel Message Confirmation:

Verify the module's operation and status by checking the kernel message log.
