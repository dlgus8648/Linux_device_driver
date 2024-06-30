
# 03_Auto_Device_file_Creation

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/e1d54135-1c07-43d3-a42e-27c2ed2f7591)

```markdown
# Linux Device Driver Module: `read_write.ko`

This README file provides instructions on how to insert a kernel module, modify device file permissions, write to the device file, and read from it in Linux.

## Description

The following steps outline the process of loading a kernel module (`read_write.ko`), setting permissions for the created device file, writing data to it, and verifying the written data.

### Step-by-Step Instructions

1. **Insert the Kernel Module**

   Use the `insmod` command to insert the `read_write.ko` kernel module into the kernel. This command requires superuser privileges, hence `sudo` is used.

   ```bash
   sudo insmod read_write.ko
   ```

   This command loads the `read_write.ko` module, which is responsible for creating a device file in the `/dev` directory.

2. **Verify Device File Creation**

   After inserting the module, verify the creation of the device file by listing the contents of the `/dev` directory. The device file created by the module is expected to be named `dummydriver`.

   ```bash
   ls /dev/dummydriver
   ```

   If the device file is successfully created, you will see an output similar to:

   ```bash
   /dev/dummydriver
   ```

3. **Set Device File Permissions**
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/fed19da1-6247-4a11-9bb1-d485eae7e86b)

   Modify the permissions of the device file to allow read and write access to all users.

   ```bash
   sudo chmod 666 /dev/dummydriver
   ```

   This command ensures that the device file can be accessed without requiring superuser privileges.

4. **Write to the Device File**

   Write data to the device file using the `echo` command. For example, write the string "This is a test" to the device file.

   ```bash
   echo "This is a test" > /dev/dummydriver
   ```

5. **Read from the Device File**

   Read the content of the device file using the `head` command. For instance, to read the first line of the device file:

   ```bash
   head -n 1 /dev/dummydriver
   ```

   The expected output will be:

   ```bash
   This is a test
   ```

6. **Write Additional Data to the Device File**

   Write another string, such as "KIMRIHYEON", to the device file.

   ```bash
   echo "KIMRIHYEON" > /dev/dummydriver
   ```

7. **Read Multiple Lines from the Device File**

   Read the first two lines of the device file to verify the written data.

   ```bash
   head -n 2 /dev/dummydriver
   ```

   The expected output will be:

   ```bash
   KIMRIHYEON
   KIMRIHYEON
   ```

