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

이 코드는 IOCTL (Input/Output Control)을 사용하는 간단한 Linux 커널 모듈입니다. IOCTL은 사용자 공간에서 커널 공간으로 데이터를 전송하거나 커널 공간에서 데이터를 가져오는 메커니즘입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **register_chrdev()** 호출
   - **문자 디바이스 등록**: `register_chrdev()` 함수는 Major 번호(`MYMAJOR = 64`)와 함께 문자 디바이스를 등록합니다.
   - 성공 시 "Device number Major: %d, Minor: %d" 메시지를 출력합니다.
   - 등록에 실패하면 에러 메시지를 출력하고, 모듈 로드를 중단합니다.

### 2. 디바이스 파일 조작 시 (열기, IOCTL 호출, 닫기)

#### 2-1. **driver_open()** 호출
   - **디바이스 파일 열기**: `fops` 구조체의 `.open` 콜백으로 `driver_open()` 함수가 호출됩니다.
   - 디바이스 파일이 열릴 때 "ioctl_example - open was called!" 메시지를 출력합니다.

#### 2-2. **my_ioctl()** 호출
   - **IOCTL 요청 처리**: `fops` 구조체의 `.unlocked_ioctl` 콜백으로 `my_ioctl()` 함수가 호출됩니다.
   - `my_ioctl()`은 전달된 IOCTL 명령어에 따라 서로 다른 작업을 수행합니다.

##### 2-2-1. **WR_VALUE** 명령 처리
   - `WR_VALUE` 명령어를 받으면 `copy_from_user()`를 통해 사용자 공간에서 `answer` 값을 커널 공간으로 복사합니다.
   - 복사 성공 시 "Update the answer to %d" 메시지를 출력합니다.

##### 2-2-2. **RD_VALUE** 명령 처리
   - `RD_VALUE` 명령어를 받으면 `copy_to_user()`를 통해 커널 공간의 `answer` 값을 사용자 공간으로 복사합니다.
   - 복사 성공 시 "The answer was copied!" 메시지를 출력합니다.

##### 2-2-3. **GREETER** 명령 처리
   - `GREETER` 명령어를 받으면 구조체 `mystruct`의 데이터를 `copy_from_user()`로 사용자 공간에서 커널로 복사합니다.
   - 복사 성공 시 "X greets to Y" 형식으로 메시지를 출력합니다. (`repeat` 횟수만큼 `name`에게 인사)

#### 2-3. **driver_close()** 호출
   - **디바이스 파일 닫기**: `fops` 구조체의 `.release` 콜백으로 `driver_close()` 함수가 호출됩니다.
   - 디바이스 파일이 닫힐 때 "ioctl_example - close was called!" 메시지를 출력합니다.

### 3. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **unregister_chrdev()** 호출
   - **문자 디바이스 해제**: `unregister_chrdev()` 함수는 등록된 문자 디바이스를 해제하고, 더 이상 사용할 수 없도록 합니다.
   - 모듈이 언로드되면 "Goodbye, Kernel" 메시지를 출력합니다.

