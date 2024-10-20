# Demo
![KakaoTalk_20240624_215329403](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/617c033a-bc28-46ef-bd37-fad01656409f)
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/5e069529-ccdb-4bad-ba0d-db29fcfaee02)

# /proc/interrupts
![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/756ae583-f42a-4997-9c82-31502db935f9)

이 코드는 GPIO 17에 대한 인터럽트 요청을 처리하는 Linux 커널 모듈입니다. GPIO 17에 상승 에지(RISING EDGE) 트리거로 인터럽트를 설정하고, 인터럽트가 발생할 때마다 인터럽트 서비스 루틴(ISR)이 호출됩니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **gpio_request()** 호출
   - **GPIO 핀 요청**: `gpio_request()` 함수는 GPIO 17을 시스템에서 사용할 수 있도록 요청합니다.
   - 실패 시 오류 메시지를 출력하고 모듈 로드를 중단합니다.

#### 1-2. **gpio_direction_input()** 호출
   - **GPIO 방향 설정**: `gpio_direction_input()` 함수로 GPIO 17을 입력 모드로 설정합니다.
   - 실패 시 오류 메시지를 출력하고, 요청한 GPIO를 해제한 후 모듈 로드를 중단합니다.

#### 1-3. **gpio_to_irq()** 호출
   - **GPIO에서 IRQ로 매핑**: `gpio_to_irq()` 함수는 GPIO 17을 대응하는 IRQ(인터럽트 요청) 번호로 매핑합니다.
   - 이 함수는 GPIO 핀을 인터럽트 요청 신호로 변환하여, 이후 인터럽트를 처리할 수 있도록 합니다.

#### 1-4. **request_irq()** 호출
   - **IRQ 요청**: `request_irq()` 함수는 지정된 IRQ 번호와 ISR(인터럽트 서비스 루틴)을 커널에 등록합니다. 
   - IRQF_TRIGGER_RISING 플래그를 사용하여 GPIO 17의 상승 에지에서 인터럽트를 트리거합니다.
   - 요청에 실패하면 오류 메시지를 출력하고, 할당된 리소스를 해제한 후 모듈 로드를 중단합니다.

### 2. 인터럽트 발생 시 (`gpio_irq_handler` 호출)
   - 인터럽트가 발생하면 **gpio_irq_handler** 함수가 호출됩니다.
   - 이 함수는 IRQ가 발생했음을 기록하고, IRQ를 성공적으로 처리했음을 반환합니다 (`IRQ_HANDLED`).

### 3. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **free_irq()** 호출
   - **IRQ 해제**: `free_irq()` 함수는 IRQ 번호와 관련된 인터럽트 핸들러를 커널에서 제거합니다.

#### 3-2. **gpio_free()** 호출
   - **GPIO 핀 해제**: `gpio_free()` 함수는 GPIO 17을 시스템에서 해제하여, 다른 프로세스나 드라이버가 이 핀을 사용할 수 있도록 합니다.
