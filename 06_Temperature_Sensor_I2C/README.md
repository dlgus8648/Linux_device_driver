![i2c_1](https://github.com/user-attachments/assets/dab6c00c-6110-4b47-bcad-26afc8a915bf)

![i2c_2](https://github.com/user-attachments/assets/9f03ccfd-22db-4d70-a78c-14c5e9e77905)

![i2c_3](https://github.com/user-attachments/assets/38bb4fe6-41df-441b-a4d7-e9fa123d77e5)

### BMP280 I2C 온도 센서 리눅스 커널 드라이버 실습 보고서

#### 1. 개요
이번 실습에서는 **BMP280** 온도 및 압력 센서를 Raspberry Pi에 연결하고, 이를 위한 I2C 기반 **리눅스 커널 드라이버**를 작성하여 디바이스 파일을 통해 온도 데이터를 읽는 방법을 배웁니다. BMP280 센서를 통해 수집된 온도 데이터는 `/dev/bmp280` 디바이스 파일에서 읽을 수 있으며, `cat` 명령어를 통해 실시간으로 온도 값을 확인할 수 있습니다. 실습을 통해 I2C 프로토콜을 사용하여 센서 데이터를 처리하고, 드라이버 작동 원리를 확인합니다.

#### 3. 실습 목표
- BMP280 I2C 기반 리눅스 커널 드라이버 작성 및 구현
- I2C 주소 확인 및 센서 연결 상태 점검
- 커널 모듈을 통해 `/dev/bmp280` 파일을 생성하고, 이를 통해 온도 값을 읽음

#### 4. 실습 절차

##### 4.1 I2C 연결 확인
BMP280 센서가 Raspberry Pi에 정상적으로 연결되었는지 확인하기 위해, `i2cdetect` 명령어를 사용하여 I2C 장치의 주소를 확인했습니다. BMP280 센서의 I2C 주소는 **0x76**으로 표시되었습니다. 이 주소를 바탕으로 I2C 통신을 설정하였습니다.

##### 4.2 커널 모듈 코드 분석
- **I2C 어댑터와 클라이언트 설정**: 
  커널 드라이버에서 I2C 버스에 접근하기 위해 `i2c_adapter`와 `i2c_client` 구조체를 사용하여 어댑터와 클라이언트를 설정했습니다.
  
- **디바이스 파일 생성**: 
  드라이버에서 `device_create()` 함수를 사용하여 `/dev/bmp280` 파일을 생성하였습니다. 이 파일을 통해 유저 공간에서 커널 공간으로 데이터를 읽고 쓸 수 있게 됩니다.

##### 4.3 커널 모듈 빌드 및 로드
다음과 같은 명령어를 사용하여 작성한 커널 모듈을 빌드하고, 커널에 로드했습니다:

```bash
$ make
$ sudo insmod bmp280_driver.ko
```

모듈이 성공적으로 로드된 후, `dmesg` 명령어를 통해 커널 로그를 확인했습니다. 아래의 출력에서 BMP280 드라이버가 추가되고, I2C 주소 0x76으로 장치가 등록된 것을 확인할 수 있었습니다.

```bash
[ 667.081599] MyDeviceDriver - Device Nr 530579456 was registered
[ 667.081211] BMP280 Driver added!
[ 667.082463] ID: 0x58
```

##### 4.4 디바이스 파일 확인
디바이스 파일이 정상적으로 생성되었는지 확인하기 위해 다음 명령어를 실행했습니다:

```bash
$ ls /dev | grep bmp280
bmp280
```

이 명령어를 통해 `/dev/bmp280` 파일이 정상적으로 생성되었음을 확인했습니다.

##### 4.5 온도 데이터 읽기
디바이스 파일을 통해 온도 데이터를 읽기 위해, `cat` 명령어를 사용했습니다:

```bash
$ cat /dev/bmp280
28.28
28.28
28.28
```

위 결과는 BMP280 센서를 통해 실시간으로 읽은 온도 값(섭씨 28.28도)을 보여줍니다. 이 값을 통해 온도가 정상적으로 읽히고 있음을 확인할 수 있었습니다.

#### 5. 실습 결과 및 결론

이번 실습에서는 BMP280 센서를 I2C 통신을 통해 Raspberry Pi와 연결하고, 커널 드라이버를 작성하여 센서 데이터를 읽어오는 과정을 성공적으로 수행했습니다. `dmesg` 로그를 통해 커널 모듈이 정상적으로 로드되고, 디바이스 파일이 생성된 것을 확인하였으며, `/dev/bmp280` 파일을 통해 온도 데이터를 성공적으로 읽어들였습니다.



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
