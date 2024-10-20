# Demo
![KakaoTalk_20240624_215329403](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/617c033a-bc28-46ef-bd37-fad01656409f)
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/5e069529-ccdb-4bad-ba0d-db29fcfaee02)

# /proc/interrupts
![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/756ae583-f42a-4997-9c82-31502db935f9)

이 코드는 GPIO 17번 핀에 대한 인터럽트를 설정하는 Linux 커널 모듈입니다. GPIO 핀에 신호 변화가 발생하면 인터럽트가 발생하며, 해당 인터럽트 서비스 루틴(ISR)이 호출됩니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **gpio_request()** 호출
   - **GPIO 핀 요청**: `gpio_request()` 함수로 GPIO 17 핀을 커널에서 사용할 수 있도록 요청합니다.
   - GPIO 17을 요청하지 못하면 에러 메시지를 출력하고 함수가 종료됩니다.

#### 1-2. **gpio_direction_input()** 호출
   - **GPIO 입력 방향 설정**: `gpio_direction_input()` 함수로 GPIO 17 핀을 입력 모드로 설정합니다.
   - 설정에 실패하면 에러 메시지를 출력하고, GPIO 핀을 해제한 후 함수가 종료됩니다.

#### 1-3. **gpio_to_irq()** 호출
   - **GPIO 핀을 인터럽트로 변환**: `gpio_to_irq()` 함수로 GPIO 17 핀이 인터럽트 번호로 매핑됩니다.
   - GPIO 핀이 어떤 인터럽트 번호에 매핑되었는지를 결정하고, 그 결과를 `irq_number` 변수에 저장합니다.

#### 1-4. **request_irq()** 호출
   - **인터럽트 요청**: `request_irq()` 함수로 GPIO 17에 대한 인터럽트를 요청합니다. 
   - 이 함수는 인터럽트가 발생했을 때 호출될 인터럽트 서비스 루틴(ISR)인 `gpio_irq_handler()`를 등록합니다.
   - 인터럽트 요청에 실패하면 에러 메시지를 출력하고 GPIO 핀을 해제한 후 함수가 종료됩니다.

#### 1-5. **성공적으로 설정된 경우**
   - GPIO 17이 인터럽트와 성공적으로 매핑되었음을 로그에 출력합니다.

### 2. 인터럽트 발생 시 (`gpio_irq_handler` 호출)
   - GPIO 17 핀에 Rising Edge 신호가 감지되면 인터럽트가 발생합니다.
   - **gpio_irq_handler()** 함수가 호출되며, "Interrupt was triggered and ISR was called!" 메시지를 출력합니다.
   - ISR이 정상적으로 처리되었음을 나타내기 위해 `IRQ_HANDLED` 값을 반환합니다.

### 3. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **free_irq()** 호출
   - **인터럽트 해제**: `free_irq()` 함수는 `irq_number`에 해당하는 인터럽트를 해제하고, 더 이상 해당 인터럽트가 발생하지 않도록 합니다.

#### 3-2. **gpio_free()** 호출
   - **GPIO 핀 해제**: `gpio_free()` 함수는 GPIO 17 핀을 시스템에서 해제하여 더 이상 사용하지 않도록 합니다.

