
# 02_Device Numbers Kernel Module

# 02_01 Insmod
![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/a628118c-a8d1-4553-a622-28000e6cf2ee)
## 설명
"Device Numbers" 모듈은 문자 디바이스를 등록하고 주요 장치 번호(major device number)를 할당하는 리눅스 커널 모듈입니다. 
이 예제는 커널에서 디바이스 번호를 다루는 방법을 실습합니다.

## 실행된 명령어
다음 명령어는 모듈을 삽입하고 등록 상태를 확인하는 데 사용되었습니다:

1. `sudo insmod dev_nr.ko`
   - 커널 모듈을 커널에 삽입합니다.
2. `cat /proc/devices | grep my_dev_nr`
   - 등록된 장치 목록을 표시하고, `my_dev_nr` 항목을 보여주도록 필터링합니다.

## 커널 로그 메시지 및 /proc/devices 출력
아래는 커널 로그 메시지와 `/proc/devices` 출력에 대한 설명입니다:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ sudo insmod dev_nr.ko
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ cat /proc/devices | grep my_dev_nr
 64 my_dev_nr
```

### 상세 설명
1. `sudo insmod dev_nr.ko`
   - 이 명령은 커널 모듈 `dev_nr.ko`를 커널에 삽입합니다. 모듈의 초기화 함수가 실행되어, 특정 주요 장치 번호와 함께 문자 디바이스가 등록됩니다.
   
2. `cat /proc/devices | grep my_dev_nr`
   - `/proc/devices` 파일은 시스템에 등록된 모든 문자 및 블록 디바이스 목록과 그들의 주요 장치 번호를 포함합니다. `grep my_dev_nr` 명령어를 사용하여, 해당 디바이스의 항목을 필터링하여 찾습니다.

### 출력 설명
- `64 my_dev_nr`
  - 이 줄은 `my_dev_nr`라는 이름의 디바이스가 주요 장치 번호 `64`로 성공적으로 등록되었음을 나타냅니다. 주요 번호는 `my_dev_nr`와 연결된 디바이스 드라이버를 고유하게 식별합니다.

## 결론
위의 단계와 출력은 "Device Numbers" 커널 모듈이 올바르게 작동함을 확인해 줍니다. 이 모듈은 `my_dev_nr`라는 문자 디바이스를 주요 장치 번호 `64`와 함께 성공적으로 등록했으며, 이 등록은 `/proc/devices` 파일을 통해 확인할 수 있습니다.

이 실습은 리눅스 커널 모듈에서 디바이스 번호를 관리하는 방법을 이해하는 데 도움이 되며, 사용자 정의 장치를 만들고 다루는 데 필요한 기초를 제공합니다.

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
