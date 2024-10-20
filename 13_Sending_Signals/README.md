
# GPIO IRQ Signal Project

This project demonstrates how to handle GPIO (General Purpose Input/Output) interrupts in a Linux environment. The project includes a userspace application and a kernel module that interact to handle GPIO signals.

## Project Structure

- `gpio_irq_signal.c`: Kernel module source code that handles GPIO interrupts.
- `testapp.c`: Userspace application that waits for signals from the kernel module.
- `Makefile`: Makefile to compile the kernel module and the userspace application.
- `README.md`: This file.

## Requirements

- Linux operating system
- GCC compiler
- Root privileges to load the kernel module and run the userspace application

## Installation and Usage

1. **Compile the Kernel Module and Userspace Application:**

   ```sh
   make
   ```

2. **Load the Kernel Module:**

   ```sh
   sudo insmod gpio_irq_signal.ko
   ```

3. **Run the Userspace Application:**

   ```sh
   sudo ./a.out
   ```

   You should see the following output indicating that the application is waiting for signals:

   ```
   PID: 2772
   Wait for signal...
   ```

![제목 없음](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6750ff92-a56f-4cc8-8d66-589ba41056fe)


4. **Trigger the GPIO Interrupt:**

   Press the button or perform the action that triggers the GPIO interrupt. You should see messages indicating that the button was pressed:

   ```
   Button was pressed!
   Button was pressed!
   ```

5. **Check Kernel Messages:**

   You can check the kernel messages using the `dmesg` command to verify that the interrupt service routine (ISR) was called:
```markdown
   ```sh
   dmesg | tail
   ```

   Expected output:

   ```
   [  765.505581] gpio_irq_signal: Userspace app with PID 2772 is registered
   [  786.404864] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  787.684285] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  788.303539] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  788.779267] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  789.318061] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  790.553854] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  791.454770] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  791.454826] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  791.902612] gpio_irq_signal: Interrupt was triggered and ISR was called!
   ```

## DEMO


https://github.com/dlgus8648/Linux_device_driver/assets/139437162/5c52e975-90ac-4c9c-8d7a-b2a39074cebc

## B. 함수 호출 순서

이 코드는 GPIO 17에서 상승 에지(Rising Edge) 신호가 감지될 때 인터럽트를 발생시키고, 사용자 공간 애플리케이션에 신호(SIGUSR1과 같은 사용자 정의 신호)를 보내는 Linux 커널 모듈입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **gpio_request()** 호출
   - **GPIO 핀 요청**: `gpio_request()` 함수로 GPIO 17 핀을 커널에서 사용할 수 있도록 요청합니다.
   - GPIO 핀을 요청하지 못하면 에러 메시지를 출력하고 함수가 종료됩니다.

#### 1-2. **gpio_direction_input()** 호출
   - **GPIO 입력 방향 설정**: `gpio_direction_input()` 함수로 GPIO 17 핀을 입력 모드로 설정합니다.
   - 설정에 실패하면 에러 메시지를 출력하고, GPIO 핀을 해제한 후 함수가 종료됩니다.

#### 1-3. **gpio_set_debounce()** 호출
   - **Debounce 설정**: `gpio_set_debounce()` 함수로 GPIO 핀에 300ms의 디바운스(debounce)를 설정하여 신호의 노이즈를 줄입니다.

#### 1-4. **gpio_to_irq()** 호출
   - **GPIO 핀을 인터럽트로 변환**: `gpio_to_irq()` 함수로 GPIO 17 핀이 인터럽트 번호로 매핑됩니다. 결과는 `irq_number` 변수에 저장됩니다.

#### 1-5. **request_irq()** 호출
   - **인터럽트 요청**: `request_irq()` 함수로 GPIO 17에 대한 인터럽트를 요청합니다. 
   - 인터럽트가 발생했을 때 호출될 인터럽트 서비스 루틴(ISR)으로 `gpio_irq_signal_handler()`를 등록합니다.
   - 인터럽트 요청에 실패하면 GPIO 핀을 해제하고 함수가 종료됩니다.

#### 1-6. **register_chrdev()** 호출
   - **문자 디바이스 등록**: `register_chrdev()` 함수로 Major 번호 `MYMAJOR = 64`를 사용하여 문자 디바이스를 등록합니다. 이 디바이스를 통해 사용자 공간 애플리케이션이 커널 모듈과 상호작용할 수 있습니다.
   - 등록에 실패하면 인터럽트를 해제하고 GPIO 핀을 해제한 후 함수가 종료됩니다.

### 2. 디바이스 파일 조작 및 IOCTL 호출

#### 2-1. **my_ioctl()** 호출 (사용자 애플리케이션 등록)
   - **IOCTL 호출**: 사용자 공간에서 `ioctl()` 함수로 `REGISTER_UAPP` 명령을 보내면 `my_ioctl()` 함수가 호출됩니다.
   - 현재 커널에서 실행 중인 태스크(`task`)를 전역 변수로 저장하여 사용자 애플리케이션이 등록됩니다.

#### 2-2. **my_close()** 호출 (디바이스 파일 닫기)
   - **디바이스 파일 닫기**: 사용자 애플리케이션이 디바이스 파일을 닫으면 `my_close()` 함수가 호출됩니다.
   - 등록된 사용자 애플리케이션을 해제합니다.

### 3. 인터럽트 발생 시 (`gpio_irq_signal_handler` 호출)
   - GPIO 17 핀에서 상승 에지(Rising Edge) 신호가 감지되면 인터럽트가 발생하고 **gpio_irq_signal_handler** 함수가 호출됩니다.

#### 3-1. **신호 전송**
   - 인터럽트가 발생하면 `send_sig_info()`를 사용하여 사용자 애플리케이션에 신호(`SIGNR = 44`)를 보냅니다.
   - 신호 전송이 실패하면 에러 메시지를 출력합니다.

### 4. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 4-1. **free_irq()** 호출
   - **인터럽트 해제**: `free_irq()` 함수로 등록된 인터럽트를 해제하여 더 이상 인터럽트가 발생하지 않도록 합니다.

#### 4-2. **gpio_free()** 호출
   - **GPIO 핀 해제**: `gpio_free()` 함수로 GPIO 17 핀을 시스템에서 해제하여 더 이상 사용할 수 없도록 합니다.

#### 4-3. **unregister_chrdev()** 호출
   - **문자 디바이스 해제**: `unregister_chrdev()` 함수로 문자 디바이스를 시스템에서 제거합니다.

### 함수 호출 순서 요약

1. **ModuleInit()** → 모듈 로드, GPIO 및 인터럽트 설정, 문자 디바이스 등록
   - `gpio_request()` → `gpio_direction_input()` → `gpio_set_debounce()` → `gpio_to_irq()` → `request_irq()` → `register_chrdev()`

2. **my_ioctl()**, **my_close()** → 사용자 공간 애플리케이션과의 상호작용
   - `ioctl()`로 사용자 애플리케이션 등록 → `my_ioctl()` 호출
   - 디바이스 파일 닫기 → `my_close()` 호출

3. **gpio_irq_signal_handler()** → 인터럽트 발생 시 신호 전송
   - 인터럽트 발생 → `gpio_irq_signal_handler()` → `send_sig_info()`로 사용자 애플리케이션에 신호 전송

4. **ModuleExit()** → 모듈 언로드, 인터럽트 및 GPIO 해제, 문자 디바이스 해제
   - `free_irq()` → `gpio_free()` → `unregister_chrdev()`

이 순서는 GPIO 17 핀에서 발생하는 인터럽트를 처리하고, 해당 이벤트를 사용자 공간 애플리케이션에 신호로 알리는 과정을 설명합니다.

