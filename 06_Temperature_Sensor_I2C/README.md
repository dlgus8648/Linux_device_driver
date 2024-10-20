![i2c_1](https://github.com/user-attachments/assets/dab6c00c-6110-4b47-bcad-26afc8a915bf)

![i2c_2](https://github.com/user-attachments/assets/9f03ccfd-22db-4d70-a78c-14c5e9e77905)

![i2c_3](https://github.com/user-attachments/assets/38bb4fe6-41df-441b-a4d7-e9fa123d77e5)

이 코드는 BMP280 온도 센서를 제어하는 I2C 드라이버로, 커널 모듈을 통해 I2C 버스에서 온도 데이터를 읽고 처리하는 기능을 제공합니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **alloc_chrdev_region()** 호출
   - **문자 디바이스 번호 할당**: `alloc_chrdev_region()` 함수는 Major 및 Minor 번호를 자동으로 할당합니다.
   - 성공 시 "Device Nr %d was registered" 메시지를 출력합니다.
   - 할당 실패 시 함수가 종료됩니다.

#### 1-2. **class_create()** 호출
   - **디바이스 클래스 생성**: `class_create()` 함수는 디바이스 클래스(`myClass`)를 생성합니다.
   - 클래스 생성에 실패하면 에러 처리를 하고, 리소스를 해제한 후 함수가 종료됩니다.

#### 1-3. **device_create()** 호출
   - **디바이스 파일 생성**: `device_create()` 함수는 `/dev/bmp280`라는 이름의 디바이스 파일을 생성합니다.
   - 실패 시 에러 처리를 하고 리소스를 해제합니다.

#### 1-4. **cdev_init()** 및 **cdev_add()** 호출
   - **cdev 초기화 및 커널 등록**: `cdev_init()` 함수는 문자 디바이스 구조체(`myDevice`)를 초기화하고, `cdev_add()` 함수는 이를 커널에 등록합니다.
   - 등록에 실패하면 에러 처리를 하고 리소스를 해제합니다.

#### 1-5. **i2c_get_adapter()** 호출
   - **I2C 어댑터 획득**: `i2c_get_adapter()` 함수는 지정된 I2C 버스(이 코드에서는 버스 1번)에 대한 어댑터를 얻습니다.

#### 1-6. **i2c_new_device()** 호출
   - **I2C 디바이스 등록**: `i2c_new_device()` 함수는 `bmp_i2c_board_info`를 사용하여 BMP280 I2C 디바이스를 생성하고, I2C 버스에 등록합니다.

#### 1-7. **i2c_add_driver()** 호출
   - **I2C 드라이버 추가**: `i2c_add_driver()` 함수는 BMP280 드라이버를 I2C 시스템에 추가합니다.

#### 1-8. **i2c_smbus_read_byte_data()** 호출
   - **센서 ID 읽기**: `i2c_smbus_read_byte_data()` 함수로 BMP280 센서의 ID 레지스터(0xD0)를 읽고, 해당 값을 출력합니다.

#### 1-9. **보정 데이터 읽기**
   - **온도 보정값 읽기**: `i2c_smbus_read_word_data()` 함수로 보정 데이터 레지스터(0x88, 0x8A, 0x8C)를 읽어와 온도 보정값을 설정합니다.

#### 1-10. **센서 설정** (초기화)
   - **센서 설정**: `i2c_smbus_write_byte_data()` 함수로 BMP280의 제어 레지스터(0xF5, 0xF4)에 값을 써서 센서를 설정합니다.

### 2. 디바이스 파일 조작 시 (열기, 읽기, 닫기)

#### 2-1. **driver_open()** 호출
   - **디바이스 파일 열기**: `fops` 구조체의 `.open` 콜백으로 `driver_open()` 함수가 호출됩니다.
   - 디바이스 파일이 열릴 때 "Open was called" 로그를 출력합니다.

#### 2-2. **driver_read()** 호출
   - **디바이스 파일에서 읽기**: `fops` 구조체의 `.read` 콜백으로 `driver_read()` 함수가 호출됩니다.
   - `read_temperature()` 함수를 통해 BMP280 센서에서 현재 온도를 읽어온 후, 해당 값을 사용자 공간으로 복사합니다.

#### 2-3. **driver_close()** 호출
   - **디바이스 파일 닫기**: `fops` 구조체의 `.release` 콜백으로 `driver_close()` 함수가 호출됩니다.
   - 디바이스 파일이 닫힐 때 "Close was called" 로그를 출력합니다.

### 3. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **i2c_unregister_device()** 호출
   - **I2C 디바이스 제거**: `i2c_unregister_device()` 함수가 BMP280 I2C 디바이스를 I2C 버스에서 제거합니다.

#### 3-2. **i2c_del_driver()** 호출
   - **I2C 드라이버 제거**: `i2c_del_driver()` 함수가 I2C 드라이버를 시스템에서 제거합니다.

#### 3-3. **cdev_del(), device_destroy(), class_destroy(), unregister_chrdev_region()** 호출
   - **디바이스 파일 및 클래스 해제**: `cdev_del()` 함수로 문자 디바이스를 해제하고, `device_destroy()`와 `class_destroy()` 함수로 디바이스 파일과 클래스를 제거합니다.
   - `unregister_chrdev_region()` 함수로 문자 디바이스 번호를 해제합니다.
   - 언로드 완료 후 "Goodbye, Kernel" 로그를 출력합니다.
