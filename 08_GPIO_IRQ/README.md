# 08_GPIO_IRQ
## 관련 개념

### 1. `request_irq()`
 장치 드라이버에서 인터럽트를 처리하기 위해서는 미리 request_irq() 함수를 통해 핸들러를 등록해야 합니다. 
• request_irq() 함수는 IRQ 번호, 처리할 핸들러 함수, 플래그, 장치 정보 등의 인자를 받습니다. 

#### 실습에 사용되어진 request_irq()함수
```c
request_irq(irq_number, (irq_handler_t) gpio_irq_handler, IRQF_TRIGGER_RISING, "my_gpio_irq", NULL) != 0)
```
1. **`irq_number`**: 
   - `gpio_to_irq(17)`로부터 가져온 값으로, GPIO 17에 대응되는 인터럽트 번호입니다. 리눅스 커널에서 하드웨어 인터럽트는 각 GPIO 핀에 대해 고유한 번호가 매핑됩니다.
   - 이 매핑된 인터럽트 번호가 `irq_number`에 저장되고, 해당 번호의 인터럽트가 발생할 때 등록된 핸들러가 호출됩니다.

2. **`(irq_handler_t) gpio_irq_handler`**:
   - 인터럽트가 발생할 때 호출되는 인터럽트 핸들러입니다.
   - `gpio_irq_handler`라는 함수는 인터럽트가 발생하면 실행될 코드입니다. 해당 핸들러는 이후에 더 자세히 설명합니다.

3. **`IRQF_TRIGGER_RISING`**:
   - 인터럽트가 발생하는 신호의 형태를 지정하는 플래그입니다. `IRQF_TRIGGER_RISING`은 GPIO 핀의 신호가 **상승 에지**(low에서 high로 변할 때)에서 인터럽트가 발생하도록 설정하는 플래그입니다.
   - 다른 플래그로는 하강 에지에서 인터럽트를 발생시키는 `IRQF_TRIGGER_FALLING` 또는 상승 및 하강 모두에서 인터럽트를 발생시키는 `IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING`이 있습니다.

4. **`"my_gpio_irq"`**:
   - 이 문자열은 인터럽트의 이름을 지정하는 부분입니다. 디버깅이나 `/proc/interrupts`와 같은 시스템 정보를 출력할 때 인터럽트가 어떤 장치와 관련되어 있는지 쉽게 식별할 수 있게 해줍니다.

5. **`NULL`**:
   - 마지막 인자는 장치에 대한 데이터 포인터로, 인터럽트 핸들러에서 특정 장치 정보를 참조할 필요가 있을 때 사용합니다. 여기서는 특별한 장치 데이터가 필요 없기 때문에 `NULL`로 설정되었습니다.

#### 반환값:
`request_irq()` 함수는 성공적으로 인터럽트를 등록하면 `0`을 반환하고, 실패하면 음수의 에러 코드를 반환합니다. 이 코드는 `request_irq()`의 반환값이 `0`이 아닌 경우 인터럽트 요청이 실패했다는 의미로, 오류 메시지를 출력하고 필요한 자원을 해제한 후 모듈을 로드하지 않도록 합니다.

### 2. 인터럽트 처리 구조: **Top Half**와 **Bottom Half**
일반적으로 디바이스 드라이버를 구현할 때, 인터럽트 처리를 나누어 구현

#### 전반부 (Top half) : 인터럽트 핸들러의 구현
- 인터럽트가 발생하지 않는 구간
- 인터럽트 핀의 신호를 빨리 끄는 것이 목적, Interrupt Clear Register 사용
- 왜냐하면, 인터럽트는 CPU에서 다른 작업들을 중단시키고 바로 처리되기 때문에, 이 단계에서 시간을 오래 소비하면 시스템의 성능에 악영향을 끼칠 수 있기 때문입니다.
- Bottom half 처리를 세팅하고 종료

#### 후반부 (Bottom half) : 하드웨어의 구체적인 처리 구현
. 인터럽트가 발생할 수 있는 구간, 오래 걸려도 알아서 스케줄링 됨
- **SoftIRQ**: 커널 수준에서 실행되며, 주로 네트워크 패킷 처리나 타이머 이벤트 등의 작업에 사용됩니다.
- **Tasklet**: SoftIRQ의 좀 더 단순한 형태로, 커널의 특정 작업을 나중에 수행할 수 있도록 스케줄링합니다.
- **Workqueue**: 프로세스 컨텍스트에서 실행되는 **Bottom Half** 메커니즘으로, Tasklet과 달리 커널의 스레드에서 작업이 처리됩니다. 이 방식은 장기적인 작업에도 적합합니다.

.

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

