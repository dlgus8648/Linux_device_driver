# 07_Temperature_Sensor_I2C(BMP280) Driver

#### 1. I2C 설정 및 센서 연결
BMP280 센서를 라즈베리 파이에 연결한 후, 다음 명령어를 사용하여 I2C 버스에서 센서가 올바르게 연결되었는지 확인하였습니다.

```bash
i2cdetect -y 1
```
위 명령어를 통해 **0x76** 주소에 BMP280 센서가 연결된 것을 확인하였습니다. 이 주소는 BMP280 센서의 I2C 슬레이브 주소로, 드라이버가 이를 기반으로 센서와 통신하게 됩니다.

#### 코드 구현
- #### 1. I2C 디바이스 ID 테이블 정의


```
static const struct i2c_device_id bmp_id[] = {
		{ SLAVE_DEVICE_NAME, 0 }, 
		{ }
};
```

   - `SLAVE_DEVICE_NAME`은 **장치의 이름**을 나타냅니다. 코드 상에서 `SLAVE_DEVICE_NAME`은 `"BMP280"`으로 정의되어 있으므로, 이 값은 `"BMP280"`을 나타냅니다.
   - 두 번째 값 `0`은 **드라이버에 대한 추가적인 정보**로 사용될 수 있으며, 주로 플래그나 사용자 정의 정보가 들어갑니다. 여기서는 특별한 정보가 없으므로 `0`으로 설정되었습니다.
   - I2C 디바이스 ID 테이블은 반드시 마지막에 **빈 항목**을 넣어야 합니다. 이것은 배열의 끝을 나타내며, 커널이 테이블을 처리할 때 끝을 알 수 있도록 해줍니다.


- #### 2. I2C 드라이버 구조체를 정의
```
static struct i2c_driver bmp_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};
```
#### 1. **`struct i2c_driver`**:
   - `i2c_driver` 구조체는 리눅스 커널에 **I2C 장치 드라이버를 등록**할 때 사용되는 구조체입니다. 
   - 이 구조체에는 해당 드라이버가 처리할 장치와 관련된 정보, 장치에 대한 초기화 및 종료 함수, 장치와의 통신 방식을 포함합니다.

#### 2. **`.driver = {}` 블록**:
   이 부분은 **I2C 드라이버의 일반적인 특성**을 정의하는 **`struct device_driver`** 구조체의 필드를 초기화하는 코드입니다. 이 필드는 드라이버의 이름, 소유권, 그리고 기타 속성을 정의합니다.

   - **`.name = SLAVE_DEVICE_NAME`**:
     - 드라이버의 이름을 지정합니다. 여기서 `SLAVE_DEVICE_NAME`은 `"BMP280"`으로 정의되어 있습니다. 이 이름은 I2C 버스에서 특정 장치가 연결되었을 때 드라이버를 매칭하는 데 사용됩니다.
     - `"BMP280"`은 드라이버가 제어할 **I2C 장치의 이름**으로 사용됩니다.

   - **`.owner = THIS_MODULE`**:
     - `THIS_MODULE`은 현재 로드된 **커널 모듈을 가리키는 매크로**입니다. 이 값은 드라이버가 **모듈 기반**으로 로드되었을 때, 해당 모듈을 참조하게 됩니다.
     - 이 필드는 모듈이 사용 중일 때 언로드되지 않도록 보호하는 데 사용됩니다. 커널은 `THIS_MODULE`을 통해 모듈의 참조 카운트를 관리하고, 드라이버가 사용 중일 때 이를 해제하려고 할 경우 오류가 발생하게 됩니다.

### 3. **구조체의 역할**
- 이 `i2c_driver` 구조체는 I2C 장치를 제어하기 위한 **드라이버**를 커널에 등록하는 데 사용됩니다. 커널은 이 구조체를 통해 해당 드라이버가 어떤 장치를 제어하는지, 드라이버의 기본적인 정보는 무엇인지 알 수 있습니다.
- 이 구조체가 등록되면 커널은 `SLAVE_DEVICE_NAME`(즉, `"BMP280"`)이라는 이름을 가진 I2C 장치가 연결되었을 때, 이를 인식하고 적절한 드라이버를 호출하여 장치와 통신할 수 있게 됩니다.

#### 
- #### 보드정보 정의
```
static struct i2c_board_info bmp_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, BMP280_SLAVE_ADDRESS)
};

```
- 보드 정보를 생성합니다.
-  장치 이름은 BMP 280
- 주소는 76 헥사입니다.

#### I2C 어댑터 정의
```
bmp_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);
 
	if(bmp_i2c_adapter != NULL) {
		bmp280_i2c_client = i2c_acpi_new_device(bmp_i2c_adapter, &bmp_i2c_board_info);
```
- ### 1. **`i2c_get_adapter(I2C_BUS_AVAILABLE)`**:
   - **역할**: I2C 버스에 접근하기 위해 **I2C 어댑터**를 가져오는 함수입니다.
   - **설명**:
     - I2C 어댑터는 I2C 버스에 연결된 장치와 통신할 수 있는 인터페이스입니다. 라즈베리 파이와 같은 시스템에서는 I2C 버스가 하나 이상 있을 수 있으며, 이를 구분하기 위해 **버스 번호**가 사용됩니다.
     - `I2C_BUS_AVAILABLE`은 사용 가능한 I2C 버스의 번호입니다. 예를 들어, 라즈베리 파이에서는 기본적으로 **I2C 버스 1**이 사용되며, 이 값을 사용하여 해당 버스에 접근할 수 있습니다.
     - 이 함수는 해당 버스에 연결된 I2C 어댑터를 반환합니다. 이 어댑터는 이후에 I2C 장치와 통신하는 데 사용됩니다.
   
   - **반환 값**:
     - 성공 시: I2C 어댑터에 대한 포인터를 반환합니다.
     - 실패 시: `NULL`을 반환하여 어댑터를 찾지 못했음을 나타냅니다.

### 2. **`i2c_acpi_new_device(bmp_i2c_adapter, &bmp_i2c_board_info)`**:
   - **역할**: 지정된 I2C 어댑터에 **새로운 I2C 장치(클라이언트)를 등록**하는 함수입니다.
   - **설명**:
     - `bmp_i2c_adapter`는 `i2c_get_adapter()`로부터 얻은 **I2C 어댑터**로, BMP280 센서가 연결된 I2C 버스에 대한 핸들입니다.
     - `bmp_i2c_board_info`는 새로운 I2C 장치에 대한 정보가 담긴 구조체입니다. 이 구조체에는 장치의 이름(예: `"BMP280"`)과 I2C 주소(0x76)가 포함되어 있습니다. 이 정보를 통해 BMP280 장치를 I2C 버스에 등록하고, 드라이버가 해당 장치와 통신할 수 있게 됩니다.
     - `i2c_acpi_new_device()` 함수는 지정된 어댑터와 보드 정보를 기반으로 새로운 I2C 장치를 커널에 등록합니다.

### Chip ID 읽기
```
	id = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xD0);
```
// 데이터 sheet
	// 먼저 읽고 자하는것은 이 칩 ID 레지스터입니다.
	// 칩 ID는 0x58로 16진수입니다.
	// 0xD0 id레지스터에 -> 있습니다.
	/* Read Chip ID */

### 온도읽기
```
	dig_T1 = i2c_smbus_read_word_data(bmp280_i2c_client, 0x88);
	dig_T2 = i2c_smbus_read_word_data(bmp280_i2c_client, 0x8a);
	dig_T3 = i2c_smbus_read_word_data(bmp280_i2c_client, 0x8c);
 
	if(dig_T2 > 32767)
		dig_T2 -= 65536;
 
	if(dig_T3 > 32767)
		dig_T3 -= 65536;
 
	/* Initialice the sensor */
	i2c_smbus_write_byte_data(bmp280_i2c_client, 0xf5, 5<<5);
  i2c_smbus_write_byte_data(bmp280_i2c_client, 0xf4, ((5<<5) | (5<<2) | (3<<0)));
	return ret;

```

// config_register -> 0xF4에서 초기화를 해줘야합니다.
	// 왜냐면 처음 시작할때 슬립모드에 있기때문에
	// 이를 정상모드로 설정해야하고
	// 샘플링 속도를 설정해야합니다.
	// 얼마나 많은 비트를 온도나 압력으로 설정할지 길이를 설정할 수 있습니다.
	// ctrl_meas에서 우리는 샘플링시간(t_sb)를 1초로 설정하겠습니다.
	// 초기화에서 이 값을 읽겠습니다.
	// 첫번째 보정 변수의 주소는 88헥사입니다.
	// 하나의 보정 변수는 워드 크기를 나타냅니다.

	// 샘플링 시간을  1초로 설정할 것입니다.
	// register 0xF5 config 우리는 1초를 사용할것이므로 t_sb = 101 5로 설정해야합니다.

 	// register 0xF4 ctrl_meas레지스터를 설정해야합니다.
	// 첫번째 두비트는 온도와 압력의 비트 너비입니다.
	// 그리고 마지막 하나는 정상 작동 모드로 설정하고자 합니다.
	// 이비트를 3으로 설정하여/ 이를 달성할 수 있습니다.
	// 이제 온도를 얻기위한 함수를 추가해야합니다.
#### 온도함수

```

s32 read_temperature(void) {
	int var1, var2;
	s32 raw_temp;

	s32 d1, d2, d3;
 
	/* Read Temperature */
	d1 = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xFA);
	d2 = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xFB);
	d3 = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xFC);
	raw_temp = ((d1<<16) | (d2<<8) | d3) >> 4;

  // d1, d2, d3를 이용하여 온도를 계산할것입니다.
	// 이는 데이터 시트의 공식을 사용한것입니다.
	/* Calculate temperature in degree */
	var1 = ((((raw_temp >> 3) - (dig_T1 << 1))) * (dig_T2)) >> 11;
 
	var2 = (((((raw_temp >> 4) - (dig_T1)) * ((raw_temp >> 4) - (dig_T1))) >> 12) * (dig_T3)) >> 14;
	return ((var1 + var2) *5 +128) >> 8;
}
```


![i2c_1](https://github.com/user-attachments/assets/dab6c00c-6110-4b47-bcad-26afc8a915bf)

![i2c_2](https://github.com/user-attachments/assets/9f03ccfd-22db-4d70-a78c-14c5e9e77905)

![i2c_3](https://github.com/user-attachments/assets/38bb4fe6-41df-441b-a4d7-e9fa123d77e5)

![i2c_2](https://github.com/user-attachments/assets/3e7157ef-54ab-444f-ad64-8bf50172c93e)
![i2c_11](https://github.com/user-attachments/assets/c0ac73e6-dc6a-4847-8d2c-4b75b4f72344)
![i2c_22](https://github.com/user-attachments/assets/92350279-6a36-455e-8e7c-6f4a4163ee29)
![i2c_메모리맵](https://github.com/user-attachments/assets/036507ef-8697-48b7-b22a-10b3a91c1049)

