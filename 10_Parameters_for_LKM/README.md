# 10_Parameters_for_LKM
## 관련 개념

### Moddule_param()을 쓰는이유
-  I/O 주소나 인터럽트 요청(IRQ) 값과 같은 하드웨어 설정 값을 드라이버에 전달해야 할 때 매개 변수를 사용하는 것이 필요합니다.
-  모듈 매개변수를 통해 커널 모듈을 컴파일하지 않고도 다양한 설정을 적용할 수 있습니다. 

### Module_param() 실습
이 코드에서 `module_param()`은 커널 모듈에서 **매개변수**를 받아 모듈의 동작을 설정하는 데 사용됩니다. 이를 통해 사용자는 모듈을 로드할 때 특정 매개변수를 전달할 수 있으며, 해당 매개변수를 커널 모듈 내에서 사용할 수 있습니다.

해당 코드에서 `module_param()`의 사용을 자세히 살펴보겠습니다:

### 1. **모듈 매개변수 선언**
```c
static unsigned int gpio_nr = 12;
static char *device_name = "testdevice";
```
- **`gpio_nr`**: `unsigned int` 타입의 변수로, 기본 값은 `12`입니다. 이는 사용자가 GPIO 번호를 전달할 수 있도록 정의된 변수입니다.
- **`device_name`**: `char *` 타입의 변수로, 기본 값은 `"testdevice"`입니다. 사용자가 장치의 이름을 문자열로 전달할 수 있도록 정의되었습니다.

이 두 변수를 `module_param()`을 통해 **모듈 매개변수**로 설정합니다.

### 2. **`module_param()`을 통한 매개변수 설정**
```c
module_param(gpio_nr, uint, S_IRUGO);
module_param(device_name, charp, S_IRUGO);
```
- **`module_param(gpio_nr, uint, S_IRUGO)`**:
  - `gpio_nr` 변수는 `unsigned int` (`uint`) 타입으로 설정됩니다.
  - `S_IRUGO`는 **파일 권한**을 나타내며, 매개변수를 **읽기 전용**으로 설정합니다. 즉, `/sys/module/<module_name>/parameters/` 경로에서 `gpio_nr`를 읽을 수 있지만 수정할 수는 없습니다.

- **`module_param(device_name, charp, S_IRUGO)`**:
  - `device_name` 변수는 **문자열** 타입 (`char *` 또는 `charp`)으로 설정됩니다.
  - 역시 `S_IRUGO`로 **읽기 전용**으로 설정되어 있습니다.

이 두 개의 `module_param()` 호출로, 모듈이 로드될 때 사용자로부터 `gpio_nr`와 `device_name` 매개변수를 전달받을 수 있습니다.

### 3. **MODULE_PARM_DESC()**
```c
MODULE_PARM_DESC(gpio_nr, "Nr. of GPIO to use in this LKM");
MODULE_PARM_DESC(device_name, "Device name to use in this LKM");
```
- **`MODULE_PARM_DESC()`**는 매개변수에 대한 설명을 추가하는 매크로입니다. 이 설명은 `/sys/module/<module_name>/parameters/` 경로에서 매개변수를 볼 때 나타납니다.
- `gpio_nr`에 대한 설명은 `"Nr. of GPIO to use in this LKM"`이며, 이는 매개변수가 어떤 용도인지 알려줍니다.
- `device_name`에 대한 설명은 `"Device name to use in this LKM"`입니다.

### 4. **모듈 로드시 매개변수 사용**
```c
static int __init ModuleInit(void) {
    printk("gpio_nr = %u\n", gpio_nr);
    printk("device_name = %s\n", device_name);
    printk("Hello, Kernel!\n");
    return 0;
}
```
모듈이 로드될 때 (`ModuleInit()` 함수가 호출될 때), `gpio_nr`와 `device_name`의 값을 `printk()`를 통해 커널 로그에 출력합니다.
- 만약 사용자가 `insmod`나 `modprobe` 명령으로 모듈을 로드할 때 매개변수를 전달했다면, 그 값을 그대로 사용하게 됩니다.
- 예를 들어, 다음과 같이 모듈을 로드할 때 매개변수를 전달할 수 있습니다:
  ```bash
  insmod my_module.ko gpio_nr=17 device_name="new_device"
  ```
  이 경우 `gpio_nr`는 17로 설정되고, `device_name`은 `"new_device"`로 설정됩니다. 그렇지 않으면, 기본값(즉, `gpio_nr = 12`, `device_name = "testdevice"`)이 사용됩니다.

### DEMO

**1. 컴파일 및 모듈 로딩**

![제목 없음](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6ea9f9af-9d7c-443a-8c68-8625ff994bda)

   - 첫 번째 명령어는 커널 모듈이 기본 매개변수를 설정하는 것을 보여줍니다.
   - (`gpio_nr = 12` 및 `device_name = testdevice`).





**2. 매개변수 변경 후 다시 로딩**

![제목 없음2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/170e117a-bd97-4476-89b1-a8dda6afa4a2)

   - 두 번째 명령어는 커널 모듈이 특정 매개변수로 로드되는 것을 보여줍니다.
   - (`device_name="dummy"` 및 `gpio_nr=2`).



### 요약
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/0102f8cf-0888-486f-b682-8af0887306d3)

이 프로젝트는 `my_params.ko`라는 커널 모듈을 사용합니다.
- 이 모듈은 **두 개의 매개변수**를 허용합니다: `device_name` 및 `gpio_nr`.
- 각 매개변수는 모듈이 초기화될 때 커널에 의해 설정됩니다.

이 코드는 Linux 커널 모듈에서 매개변수를 사용하는 방법을 보여줍니다. 모듈이 로드될 때 매개변수로 지정된 값을 받아들이고, 이를 출력하는 간단한 모듈입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **매개변수 값 읽기**
   - `module_param()`을 통해 정의된 커널 모듈 매개변수 `gpio_nr`와 `device_name`은 모듈이 로드될 때 커널로부터 값을 가져옵니다.
   - 매개변수는 모듈이 로드될 때 명령줄에서 지정할 수 있으며, 지정하지 않으면 기본값(예: `gpio_nr = 12`, `device_name = "testdevice"`)이 사용됩니다.

#### 1-2. **매개변수 값 출력**
   - **printk()**를 사용하여 `gpio_nr`와 `device_name`의 값을 출력합니다.
   - "gpio_nr = %u", "device_name = %s" 등의 메시지를 커널 로그에 기록합니다.

### 2. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 2-1. **Goodbye 메시지 출력**
   - **printk()**를 사용하여 "Goodbye, Kernel" 메시지를 출력합니다.
