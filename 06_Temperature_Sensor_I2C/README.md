# 07_Temperature_Sensor_I2C(BMP280) Driver
#### 참고. 데이터시트
[BMP280.PDF](https://github.com/user-attachments/files/17457345/BMP280.PDF)
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


- #### 2. I2C 드라이버 구조체를 정의
```
static struct i2c_driver bmp_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};
```

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

### Chip ID 읽기
![i2c_메모리맵](https://github.com/user-attachments/assets/036507ef-8697-48b7-b22a-10b3a91c1049)
```
	id = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xD0);
```


### 온도읽기
![i2c_2](https://github.com/user-attachments/assets/3e7157ef-54ab-444f-ad64-8bf50172c93e)

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


#### 온도함수
![i2c_22](https://github.com/user-attachments/assets/92350279-6a36-455e-8e7c-6f4a4163ee29)
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
#### DEMO 사진
![i2ccccccc글미](https://github.com/user-attachments/assets/3ada72d5-76b9-4ba3-bf43-49cd799b0309)

![i2c_1](https://github.com/user-attachments/assets/dab6c00c-6110-4b47-bcad-26afc8a915bf)

![i2c_2](https://github.com/user-attachments/assets/9f03ccfd-22db-4d70-a78c-14c5e9e77905)

![i2c_3](https://github.com/user-attachments/assets/38bb4fe6-41df-441b-a4d7-e9fa123d77e5)



