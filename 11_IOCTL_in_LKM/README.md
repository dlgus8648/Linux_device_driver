# ioctl_example Module

## 1. Module Loading and Initialization Message:

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/c18b2dab-102c-4937-8840-219ff8a1db57)

After initializing the module, the kernel prints the message "Hello, Kernel!" to indicate that the initialization was successful.  
The module indicates that the registered device number has a `Major number of 64` and a `Minor number of 0.`

## 2. Device Node Creation:

![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/7c987dc2-9369-46c3-ab9d-0c6f5c651953)

A device node named `/dev/dummy` has been created with `Major number 64` and `Minor number 0`.  
This node provides an interface to interact with the `ioctl_example` module.

## 3. User Space Program Execution and Result Verification:

![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6702fb92-8d94-4679-a1b1-da30092c1857)

The `./test` program executed in user space interacts with the `ioctl_example` module.  
The first message prints the default response of 42.  
The second message indicates that the response has been updated to 123.  
A message indicating that the device has been successfully opened is displayed.

## 4. Kernel Message Confirmation:

![4](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/054508a1-4398-49b3-b58b-8f3ebb6e3779)

Verify the module's operation and status by checking the kernel message log.
