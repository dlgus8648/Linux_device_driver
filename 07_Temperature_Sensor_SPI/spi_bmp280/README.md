![spi_dev_2](https://github.com/user-attachments/assets/951f57e7-7ea1-4bc4-a7e4-3e4640f93cd9)
![spi_dev_1](https://github.com/user-attachments/assets/5c0d8c63-acd5-4fa7-bcd5-a80e1c665009)
![spi_dev_4](https://github.com/user-attachments/assets/dca1ae1c-02d6-4386-83e5-41c10642d110)

이 코드는 SPI 인터페이스를 통해 BMP280 센서의 레지스터를 읽고 쓰는 Linux 커널 모듈입니다. 이 모듈은 SPI 버스에 BMP280 센서를 연결하고, 특정 레지스터 값을 읽거나 쓰기 위한 목적으로 사용됩니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **spi_busnum_to_master()** 호출
   - **SPI 마스터 가져오기**: `spi_busnum_to_master()` 함수는 지정된 SPI 버스 번호(MY_BUS_NUM)에서 마스터 장치를 가져옵니다.
   - SPI 버스가 존재하지 않으면 오류 메시지를 출력하고 함수가 종료됩니다.

#### 1-2. **spi_new_device()** 호출
   - **새로운 SPI 디바이스 생성**: `spi_new_device()` 함수는 `spi_device_info` 구조체의 설정을 기반으로 새로운 SPI 디바이스(bmp280_dev)를 생성합니다.
   - 장치가 생성되지 않으면 오류 메시지를 출력하고 함수가 종료됩니다.

#### 1-3. **spi_setup()** 호출
   - **SPI 버스 설정**: `spi_setup()` 함수는 SPI 디바이스의 설정을 적용합니다. 여기에는 `bits_per_word`와 같은 SPI 버스의 파라미터가 포함됩니다.
   - 설정에 실패하면 오류 메시지를 출력하고, SPI 디바이스를 등록 해제한 후 함수가 종료됩니다.

#### 1-4. **spi_w8r8()** 호출 (Chip ID 읽기)
   - **Chip ID 읽기**: `spi_w8r8()` 함수는 BMP280 센서의 ID 레지스터(0xD0)를 읽습니다.
   - 읽어온 ID 값을 출력합니다.

#### 1-5. **spi_write()** 및 **spi_w8r8()** 호출 (Config 레지스터 설정 및 읽기)
   - **Config 레지스터 쓰기**: `spi_write()` 함수로 BMP280의 설정 레지스터(0xF5)에 값을 씁니다. `val` 배열에 지정된 데이터를 전송합니다.
   - **Config 레지스터 값 읽기**: `spi_w8r8()` 함수로 설정된 Config 레지스터의 값을 읽고 출력합니다.

### 2. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 2-1. **spi_unregister_device()** 호출
   - **SPI 디바이스 제거**: `spi_unregister_device()` 함수는 SPI 디바이스(bmp280_dev)를 SPI 버스에서 제거합니다.
   - BMP280 디바이스가 등록되어 있으면 이를 해제한 후 로그 메시지를 출력하고 종료됩니다.

