https://github.com/dlgus8648/Linux_device_driver/assets/139437162/e47dd496-e3ac-4e8c-8b6d-452d351b527c

## B. 함수 호출 순서
이 코드는 GPIO 17에서 상승 에지(Rising Edge) 신호가 감지될 때 인터럽트를 발생시키고, 사용자 공간 애플리케이션이 `poll()` 시스템 호출을 통해 이벤트를 대기하고 처리할 수 있도록 하는 Linux 커널 모듈입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **init_waitqueue_head()** 호출
   - **waitqueue 초기화**: `init_waitqueue_head()` 함수로 `waitqueue`를 초기화합니다. 이 대기열은 이후 `poll()`을 사용하는 사용자 공간 애플리케이션이 대기할 수 있는 공간으로 사용됩니다.

#### 1-2. **gpio_request()** 호출
   - **GPIO 핀 요청**: `gpio_request()` 함수로 GPIO 17 핀을 커널에서 사용할 수 있도록 요청합니다.
   - GPIO 핀을 요청하지 못하면 에러 메시지를 출력하고 함수가 종료됩니다.

#### 1-3. **gpio_direction_input()** 호출
   - **GPIO 입력 방향 설정**: `gpio_direction_input()` 함수로 GPIO 17 핀을 입력 모드로 설정합니다.
   - 설정에 실패하면 에러 메시지를 출력하고, GPIO 핀을 해제한 후 함수가 종료됩니다.

#### 1-4. **gpio_set_debounce()** 호출
   - **Debounce 설정**: `gpio_set_debounce()` 함수로 GPIO 핀에 300ms의 디바운스를 설정하여 신호의 노이즈를 줄입니다.

#### 1-5. **gpio_to_irq()** 호출
   - **GPIO 핀을 인터럽트로 변환**: `gpio_to_irq()` 함수로 GPIO 17 핀이 인터럽트 번호로 매핑됩니다. 결과는 `irq_number` 변수에 저장됩니다.

#### 1-6. **request_irq()** 호출
   - **인터럽트 요청**: `request_irq()` 함수로 GPIO 17에 대한 인터럽트를 요청합니다. 
   - 인터럽트가 발생했을 때 호출될 인터럽트 서비스 루틴(ISR)으로 `gpio_irq_poll_handler()`를 등록합니다.
   - 인터럽트 요청에 실패하면 GPIO 핀을 해제하고 함수가 종료됩니다.

#### 1-7. **register_chrdev()** 호출
   - **문자 디바이스 등록**: `register_chrdev()` 함수로 Major 번호 `MYMAJOR = 64`를 사용하여 문자 디바이스를 등록합니다. 이 디바이스를 통해 사용자 공간 애플리케이션이 `poll()` 시스템 호출을 사용해 대기열에 대기할 수 있습니다.
   - 등록에 실패하면 인터럽트를 해제하고 GPIO 핀을 해제한 후 함수가 종료됩니다.

### 2. 인터럽트 발생 시 (`gpio_irq_poll_handler` 호출)
   - GPIO 17 핀에서 상승 에지(Rising Edge) 신호가 감지되면 인터럽트가 발생하고 **gpio_irq_poll_handler** 함수가 호출됩니다.

#### 2-1. **wake_up() 호출**
   - 인터럽트가 발생하면 `irq_ready` 변수를 1로 설정하여 인터럽트가 발생했음을 나타내고, `wake_up()` 함수를 호출하여 대기 중인 `waitqueue`에 있는 사용자 공간 애플리케이션을 깨웁니다.

### 3. 사용자 애플리케이션에서 `poll()` 호출 시 (`my_poll` 호출)
   - 사용자 공간에서 `poll()` 시스템 호출이 발생하면 **my_poll** 함수가 호출됩니다.

#### 3-1. **poll_wait() 호출**
   - **poll_wait**를 사용하여 커널이 `waitqueue`에서 대기하도록 설정합니다. 애플리케이션은 `waitqueue`에 있는 동안 인터럽트가 발생할 때까지 대기합니다.

#### 3-2. **POLLIN 반환**
   - `irq_ready`가 1인 경우, `POLLIN` 값을 반환하여 인터럽트가 발생했음을 사용자 애플리케이션에 알립니다. 이후 `irq_ready` 값을 다시 0으로 설정하여 다음 인터럽트를 기다립니다.

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
   - `init_waitqueue_head()` → `gpio_request()` → `gpio_direction_input()` → `gpio_set_debounce()` → `gpio_to_irq()` → `request_irq()` → `register_chrdev()`

2. **gpio_irq_poll_handler()** → 인터럽트 발생 시
   - 인터럽트 발생 → `irq_ready = 1` → `wake_up()`로 `waitqueue`에 대기 중인 프로세스를 깨움

3. **my_poll()** → `poll()` 시스템 호출 시
   - `poll_wait()`로 대기
   - `irq_ready`가 1인 경우 `POLLIN` 반환, `irq_ready`를 0으로 재설정

4. **ModuleExit()** → 모듈 언로드, 인터럽트 및 GPIO 해제, 문자 디바이스 해제
   - `free_irq()` → `gpio_free()` → `unregister_chrdev()`

이 순서는 인터럽트가 발생할 때 `poll()`을 사용하는 사용자 애플리케이션에 이벤트를 전달하는 과정을 설명합니다.
