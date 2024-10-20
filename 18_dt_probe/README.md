## A. Demo
![dt_probe](https://github.com/user-attachments/assets/7c04872f-83d5-4622-845b-1bc227e85e29)
![dt_probe2](https://github.com/user-attachments/assets/846eaa94-59ef-464e-8041-9d8ea239f9ef)
![dt_probe3](https://github.com/user-attachments/assets/4c6de300-00e4-46a2-a61b-5082dd37db3f)



## B. 함수 호출 순서

이 코드는 플랫폼 드라이버가 로드될 때 장치 트리(Device Tree)에서 특정 장치 및 해당 속성을 파싱하여 처리하는 Linux 커널 모듈입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`my_init` 호출)
   - `module_init()` 매크로에 의해 **my_init** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **platform_driver_register()** 호출
   - **플랫폼 드라이버 등록**: `platform_driver_register()` 함수로 `my_driver` 구조체에 정의된 플랫폼 드라이버를 커널에 등록합니다.
   - 드라이버가 등록되면 커널은 장치 트리에 정의된 장치와 해당 드라이버의 호환성을 확인하고, 호환되는 장치가 있는 경우 `dt_probe()` 함수를 호출하여 장치를 처리합니다.
   - 등록에 실패하면 에러 메시지를 출력하고 함수가 종료됩니다.

### 2. 드라이버가 등록된 장치 트리와 매칭될 때 (`dt_probe` 호출)
   - 플랫폼 장치가 드라이버와 매칭되면 **dt_probe** 함수가 호출됩니다.

#### 2-1. **device_property_present()** 호출 (속성 확인)
   - **속성 존재 여부 확인**: `device_property_present()` 함수를 사용해 장치 트리에서 `label`과 `my_value` 속성이 있는지 확인합니다.
   - 속성이 없으면 에러 메시지를 출력하고 `-1`을 반환하여 프로브 과정을 중지합니다.

#### 2-2. **device_property_read_string()** 및 **device_property_read_u32()** 호출 (속성 읽기)
   - **속성 읽기**: `device_property_read_string()`으로 `label` 속성을 읽고, `device_property_read_u32()`로 `my_value` 속성을 읽습니다.
   - 읽기에 실패하면 에러 메시지를 출력하고 함수가 종료됩니다.
   - 성공적으로 속성을 읽으면 해당 값을 출력합니다.

### 3. 모듈 언로드 시 (`my_exit` 호출)
   - `module_exit()` 매크로에 의해 **my_exit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **platform_driver_unregister()** 호출
   - **플랫폼 드라이버 등록 해제**: `platform_driver_unregister()` 함수로 등록된 플랫폼 드라이버를 시스템에서 해제합니다.
   - 이로 인해 더 이상 해당 장치에 대한 처리를 수행하지 않게 됩니다.

### 함수 호출 순서 요약

1. **my_init()** → 모듈 로드, 플랫폼 드라이버 등록
   - `platform_driver_register()`로 플랫폼 드라이버 등록

2. **dt_probe()** → 장치가 드라이버와 매칭될 때 호출
   - `device_property_present()`로 장치 트리 속성 확인
   - `device_property_read_string()` 및 `device_property_read_u32()`로 속성 읽기

3. **my_exit()** → 모듈 언로드, 플랫폼 드라이버 해제
   - `platform_driver_unregister()`로 플랫폼 드라이버 해제

이 순서는 플랫폼 드라이버가 장치 트리에서 정의된 특정 장치와 매칭될 때 해당 속성을 파싱하여 처리하는 과정을 설명합니다.
