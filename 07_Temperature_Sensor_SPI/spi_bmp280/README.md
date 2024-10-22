# 
## B. Demo
해당 실습은 bmp280 ID값을 SPI통신으로 읽어오는 실습으로 준비했습니다.





### 1. **변수 및 정의**

```c
#define MY_BUS_NUM 0
static struct spi_device *bmp280_dev;
```

- **MY_BUS_NUM**: 사용할 **SPI 버스 번호**를 정의한 매크로입니다. 이 코드에서는 **SPI 버스 번호 0**을 사용합니다.
- **bmp280_dev**: **BMP280** 장치를 나타내는 **spi_device 구조체** 포인터입니다. 이 구조체는 BMP280 센서에 대한 SPI 장치 정보를 담습니다.

---

### 2. **SPI 버스에 연결된 SPI Master 가져오기**

```c
master = spi_busnum_to_master(MY_BUS_NUM);
if(!master) {
	printk("There is no spi bus with Nr. %d\n", MY_BUS_NUM);
	return -1;
}
```

- **spi_busnum_to_master()**: 지정한 버스 번호(MY_BUS_NUM)에 해당하는 **SPI 마스터**를 가져오는 함수입니다. SPI 마스터는 SPI 버스를 관리하는 주체이며, 해당 SPI 버스에 연결된 **슬레이브 장치들**을 제어합니다.
- **master**가 `NULL`이면 지정한 SPI 버스가 존재하지 않으므로 에러를 출력하고 모듈 로드를 중단합니다.

### 3. **새로운 SPI 장치 등록**

```c
bmp280_dev = spi_new_device(master, &spi_device_info);
if(!bmp280_dev) {
	printk("Could not create device!\n");
	return -1;
}
```

- **spi_new_device()**: SPI 마스터와 **BMP280 센서 장치**를 연결하기 위한 함수입니다. 이 함수는 SPI 마스터와 연결된 **새로운 SPI 장치**를 등록합니다. **spi_device_info** 구조체는 새로운 장치의 **속성(장치 이름, 속도, 모드 등)**을 설정한 값입니다.
- **bmp280_dev**: BMP280 장치의 SPI 정보를 나타내는 **spi_device 구조체**입니다. 이 구조체는 BMP280 센서와 관련된 SPI 장치 속성을 관리합니다.

#### 4 **SPI 장치 속성 설정 및 SPI 버스 설정**

```c
bmp280_dev -> bits_per_word = 8;
if(spi_setup(bmp280_dev) != 0){
	printk("Could not change bus setup!\n");
	spi_unregister_device(bmp280_dev);
	return -1;
}
```

- **bits_per_word**: BMP280 센서는 **8비트 데이터 전송**을 하기 때문에, **bits_per_word** 속성을 **8**로 설정합니다.
- **spi_setup()**: 설정된 SPI 장치 속성에 맞게 **SPI 버스 설정**을 적용하는 함수입니다. 만약 설정에 실패하면 에러 메시지를 출력하고, SPI 장치를 해제한 뒤 모듈 로드를 중단합니다.

#### 5. **BMP280 센서 레지스터 읽기**

```c
id = spi_w8r8(bmp280_dev, 0xD0);
printk("Chip ID: 0x%x\n", id);
```

- **spi_w8r8()**: BMP280 센서의 **0xD0 레지스터**를 읽어 **Chip ID**를 가져오는 함수입니다. **0xD0**은 BMP280 센서의 **칩 ID 레지스터**로, 해당 레지스터 값을 읽으면 BMP280의 칩 ID를 확인할 수 있습니다.
- 이 값은 BMP280의 고유한 **칩 ID**를 반환하며, 이를 커널 로그에 출력합니다.

#### 6. **BMP280 센서 설정 레지스터 쓰기 및 읽기**

```c
u8 val[] = {0x75, 0x40};
spi_write(bmp280_dev, val, sizeof(val));
id = spi_w8r8(bmp280_dev, 0xF5);
printk("Config Reg. value: 0x%x\n", id);
```

- **spi_write()**: BMP280 센서의 **0x75 레지스터**에 **0x40** 값을 쓰는 함수입니다. **val[]** 배열에는 **레지스터 주소와 쓸 값**을 담고 있습니다. 첫 번째 값은 **레지스터 주소**(0x75), 두 번째 값은 **설정 값**(0x40)입니다.
- **spi_w8r8()**: BMP280 센서의 **0xF5 레지스터**(구성 레지스터)를 읽어 **현재 설정 값**을 확인합니다. 그 값을 커널 로그에 출력합니다.


#### 7. **SPI 장치 정보**

```c
struct spi_board_info spi_device_info = {
	.modalias = "bmp280",
	.max_speed_hz = 1000000,
	.bus_num = MY_BUS_NUM,
	.chip_select = 0,
	.mode = 3,
};
```

- **modalias**: 커널에 장치를 등록할 때 사용되는 **장치의 이름**입니다. 여기서는 "bmp280"으로 정의되어 있으며, 이는 커널에서 이 장치가 **BMP280 센서**임을 나타냅니다.
- **max_speed_hz**: SPI 버스에서 **최대 전송 속도**를 설정합니다. 여기서는 **1MHz**로 설정됩니다.
- **bus_num**: 사용할 **SPI 버스 번호**입니다. 위에서 정의한 **MY_BUS_NUM**(0번 버스)을 사용합니다.
- **chip_select**: **칩 선택 핀** 번호입니다. 이 코드에서는 **0**번 칩 선택 신호를 사용합니다.
- **mode**: SPI 장치의 **동작 모드**를 설정합니다. BMP280은 **SPI 모드 3**을 사용합니다. 이는 클록 신호(CPOL)와 클록 위상(CPHA)에 따라 데이터를 전송하는 SPI 통신 모드입니다.



![spi_dev_2](https://github.com/user-attachments/assets/951f57e7-7ea1-4bc4-a7e4-3e4640f93cd9)
![spi_dev_1](https://github.com/user-attachments/assets/5c0d8c63-acd5-4fa7-bcd5-a80e1c665009)
![spi_dev_4](https://github.com/user-attachments/assets/dca1ae1c-02d6-4386-83e5-41c10642d110)


