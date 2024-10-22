# Development Linux Device Driver Project

- 면접 시간의 제약으로 인해 제 리눅스 커널 및 디바이스 드라이버 개발 능력을 충분히 보여드리기 어려워, 이를 상세히 검증받기 위해 해당 레포지토리를 준비하였습니다. 
- 자료 준비도 면접의 한 과정이기에 레포지토리의 코드와 실습, 관련 개념을 서술하여 제 리눅스 디바이스 드라이버 관련 직무역량을 철저하게 검증받겠습니다.
- 섹션 A에서는 각 폴더마다 Raspberry Pi 4B(커널 5.x 버전)로 실습한 내용을 포함했습니다.
- 각 실습은 해당 개념을 대표하는 한 가지 주제를 선택하여 진행하였으며, 각 폴더 옆에는 관련 개념의 키워드를 나열하여 각 폴더에서 해당 개념들의 설명을 자세히 설명하겠습니다.
- 섹션 B에서는 리눅스OS에서 사용자프로그램이 하드웨어 제어하기 필요한 개념인 `디바이스`가 무엇인지, `드라이버`가 무엇인지 설명하기 위해 사용자 영역에서 `read`와 `write` 시스템 콜이 호출될 때, 디바이스 파일, 드라이버, 주번호, 부번호의 개념을 설명하였습니다.

## A. Linux Device Driver Project



|Project|Features|
|---|---|
|[1. Hello World Linux Kernel Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/01_Hello_World)|---|
|[2. Device Numbers and Files](https://github.com/dlgus8648/Linux_device_driver/tree/main/02_Device_Numbers)|- Register_chrdev()|
|[3. Auto Device File creation & Read - Write - Callback](https://github.com/dlgus8648/Linux_device_driver/tree/main/03_Auto_Device_file_Creation)|- alloc_chrdev_region()<br>- Device_class()<br>- cdev() |
|[4. GPIO driver](https://github.com/dlgus8648/Linux_device_driver/tree/main/04_GPIO_Driver)|---|
|[5. PWM Driver](https://github.com/dlgus8648/Linux_device_driver/tree/main/05_PWM_Driver)|---|
|[06_Temperature_Sensor_I2C](https://github.com/dlgus8648/Linux_device_driver/tree/main/06_Temperature_Sensor_I2C)|---|
|[07_Temperature_Sensor_SPI/spi_bmp280](https://github.com/dlgus8648/Linux_device_driver/tree/main/07_Temperature_Sensor_SPI/spi_bmp280)|---|
|[8. GPIO_IRQ](https://github.com/dlgus8648/Linux_device_driver/tree/main/08_GPIO_IRQ)|- request_irq<br>- Top half & bottom half|
|[9. High Resolution Timer in a Linux Kerenel Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/09_High_Resolution_Timer)|- hrtimer|
|[10. Parameters for a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/10_Parameters_for_LKM)|- module_param()|
|[11. IOCTL in a Linux kerenl module](https://github.com/dlgus8648/Linux_device_driver/tree/main/11_IOCTL_in_LKM)|---|
|[12. Treads in a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/12_Threads_in_LKM)|- kthread()<br>- kernel_thread()|
|[13. Sending a signal from Kerenl to Userspace](https://github.com/dlgus8648/Linux_device_driver/tree/main/13_Sending_Signals)|HW-인터럽트|
|[14. The Poll Callback in a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/14_The_Poll_Callback_in_LKM)|HW-폴링|
|[15. Waitqueues in a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/15_Waitqueues_in_LKM)|- 블록킹<br>- 스케줄링|
|[16_Mutex](https://github.com/dlgus8648/Linux_device_driver/tree/main/16_Mutex)|- mutex<br>- sempahore<br>- spinlock<br>- seqlock|
|[17_Misc](https://github.com/dlgus8648/Linux_device_driver/tree/main/17_Misc)|---|
|[18_dt_probe](https://github.com/dlgus8648/Linux_device_driver/tree/main/18_dt_probe)|- Device tree<br>- probe()<br>- platform_driver()|
|[19_DMA](https://github.com/dlgus8648/Linux_device_driver/tree/main/19_DMA)|-Completion<br>- DMA|
|[20_Kobject](https://github.com/dlgus8648/Linux_device_driver/tree/main/20_Kobject)|- sysfs<br>- 참조카운트<br>- kset|


---
## B. Linux Devcie & Driver

![image](https://github.com/user-attachments/assets/2fe93989-4b65-4a44-b943-772df4b5c844)

### B.1 디바이스 파일 (/dev/디바이스 파일)이란

디바이스 파일은 리눅스 시스템에서 하드웨어 장치를 파일 시스템을 통해 추상화한 특수 파일입니다.
이 파일을 통해 하드웨어 장치를 마치 일반 파일처럼 읽고 쓸 수 있습니다. 디바이스 파일은 `/dev` 디렉터리 아래에 위치하며, 유저 공간에서 이 파일에 대한 읽기(read), 쓰기(write) 작업을 통해 실제 하드웨어와 상호작용하게 됩니다.
디바이스 파일은 **Major 번호**와 **Minor 번호**로 구분됩니다. 
- **Major 번호**는 커널이 해당 디바이스 파일을 처리할 때 사용할 드라이버를 결정하는 번호입니다. 
- **Minor 번호**는 드라이버 내에서 개별 장치를 식별하는 번호입니다.

### B.2 드라이버란

드라이버는 유저 영역과 하드웨어 간의 인터페이스 역할을 수행하는 소프트웨어입니다. 커널 공간에서 동작하며, 하드웨어 장치와의 직접적인 상호작용을 담당합니다. 사용자가 `/dev/디바이스파일`을 통해 하드웨어와 상호작용하려고 할 때, 커널은 해당 디바이스 파일의 Major 번호를 통해 올바른 드라이버를 찾습니다. 그 후, 드라이버는 Minor 번호를 기반으로 구체적인 장치와의 상호작용을 처리합니다.

### B.3 유저 영역에서의 read, write 시스템 호출

**시스템 콜**은 유저 공간의 응용 프로그램이 커널에 특정 기능을 요청하는 메커니즘입니다. 예를 들어, 유저 영역의 코드에서 `/dev/디바이스파일`에 대해 `read()`나 `write()`와 같은 시스템 호출을 수행하면, 커널은 해당 디바이스 파일의 Major 번호와 Minor 번호를 참조하여 알맞은 드라이버를 탐색합니다. 

이 드라이버는 `file_operations` 구조체에 등록된 `read`와 `write` 함수에 대한 포인터를 통해 시스템 호출을 처리합니다. 구체적으로:
- **read() 시스템 콜**은 커널이 하드웨어로부터 데이터를 읽어와서 이를 유저 공간의 버퍼로 복사하는 과정입니다.
- **write() 시스템 콜**은 유저 공간에서 받은 데이터를 커널이 하드웨어로 전달하는 과정입니다.


### B.4 시스템 호출 흐름 설명

1. 유저 영역에서 `read(fd, buff, size)` 또는 `write(fd, buff, size)` 시스템 호출이 발생합니다.
2. 해당 호출은 `/dev/디바이스파일`로 전달되고, 커널은 파일의 Major 번호와 Minor 번호를 참조하여 적절한 드라이버를 탐색합니다.
3. 드라이버에서 `file_operations` 구조체에 정의된 `read()` 또는 `write()` 함수가 호출됩니다.
4. `read()`는 커널 버퍼에서 유저 공간 버퍼로 데이터를 복사(`copy_to_user`)하고, `write()`는 유저 공간 버퍼의 데이터를 커널 버퍼로 복사(`copy_from_user`)합니다.
5. 최종적으로 커널은 하드웨어 장치와 데이터를 주고받고, 결과를 유저 공간으로 반환합니다.

이러한 디바이스, 드라이버, 시스템 콜 개념이 리눅스에서 유저공간이 하드웨어 장치를 제어하는 메커니즘입니다.

