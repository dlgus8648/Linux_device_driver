# 10_Parameters_for_LKM


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
