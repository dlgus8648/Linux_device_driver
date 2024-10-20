
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

이 코드는 두 개의 커널 스레드를 생성하여 실행하는 간단한 Linux 커널 모듈입니다. 각 스레드는 주기적으로 메시지를 출력하며, 모듈이 언로드될 때 스레드가 종료됩니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **kthread_create()** 호출 (첫 번째 스레드 생성)
   - **첫 번째 커널 스레드 생성**: `kthread_create()` 함수로 `thread_function`을 실행하는 첫 번째 스레드(`kthread_1`)를 생성합니다.
   - 성공적으로 스레드가 생성되면 `wake_up_process()` 함수로 스레드를 시작합니다.
   - 실패 시 "Thread 1 could not be created!" 메시지를 출력하고, 함수가 종료됩니다.

#### 1-2. **kthread_run()** 호출 (두 번째 스레드 생성 및 실행)
   - **두 번째 커널 스레드 생성 및 실행**: `kthread_run()` 함수는 `thread_function`을 실행하는 두 번째 스레드(`kthread_2`)를 생성하고 바로 실행합니다.
   - 성공 시 "Thread 2 was created and is running now!" 메시지를 출력합니다.
   - 실패 시 "Thread 2 could not be created!" 메시지를 출력하고, 첫 번째 스레드(`kthread_1`)를 중지한 후 함수가 종료됩니다.

#### 1-3. **모든 스레드가 정상적으로 실행 중** 
   - 두 스레드가 성공적으로 생성되면 "Both threads are running now!" 메시지를 출력합니다.

### 2. 스레드 실행 중 (`thread_function` 호출)
   - 각 스레드는 **thread_function** 함수에 의해 실행됩니다.

#### 2-1. **주기적으로 메시지 출력**
   - 각 스레드는 무한 루프(`kthread_should_stop()`가 `false`일 때까지)를 통해 반복 실행됩니다.
   - `printk()`로 스레드 번호(`t_nr`)와 카운터 값(`i`)를 주기적으로 출력하며, `msleep()` 함수로 해당 스레드는 `t_nr`에 따라 1초 또는 2초 동안 대기합니다.

#### 2-2. **스레드 종료 조건 확인**
   - 루프는 `kthread_should_stop()` 함수가 `true`를 반환할 때까지 계속되며, 스레드가 종료될 때 "Thread X finished execution!" 메시지를 출력하고 종료됩니다.

### 3. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **kthread_stop()** 호출 (스레드 중지)
   - **스레드 종료**: `kthread_stop()` 함수를 호출하여 첫 번째 스레드(`kthread_1`)와 두 번째 스레드(`kthread_2`)를 중지합니다.
   - 중지되면 스레드가 `thread_function` 루프에서 빠져나와 종료됩니다.
   - "Stop both threads" 메시지를 출력합니다.

