# Linux Device Driver Development Practice 

- 면접 시간의 제약으로 인해 제 리눅스 커널 및 디바이스 드라이버 개발 능력을 충분히 보여드리기 어려워, 이를 상세히 검증받기 위해 해당 레포지토리를 준비하였습니다. 
- 이 레포지토리의 코드와 실습, 개념을 통해 제 리눅스 디바이스 드라이버 관련 직무역량을 철저하게 검증받겠습니다.
- 섹션 A에서는 각 폴더마다 Raspberry Pi 4B(커널 5.x 버전)로 실습한 내용을 포함했습니다.
- 각 실습은 해당 개념을 대표하는 한 가지 주제를 선택하여 진행하였으며, 각 폴더 옆에는 관련 개념의 키워드를 나열하여 각 폴더에서 해당 개념들의 설명을 자세히 설명하겠습니다.
- 섹션 B에서는 디바이스가 무엇인지, 드라이버가 무엇인지 설명하기 위해 사용자 영역에서 `read`와 `write` 시스템 콜이 호출될 때, 디바이스 파일, 드라이버, 주번호, 부번호의 개념을 설명하였습니다.

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
|[9. High Resolution Timer in a Linux Kerenel Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/09_High_Resolution_Timer)|-hrtimer|
|[10. Parameters for a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/10_Parameters_for_LKM)|-module_param()|
|[11. IOCTL in a Linux kerenl module](https://github.com/dlgus8648/Linux_device_driver/tree/main/11_IOCTL_in_LKM)|---|
|[12. Treads in a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/12_Threads_in_LKM)|-kthread()<br>kernel_thread()|
|[13. Sending a signal from Kerenl to Userspace](https://github.com/dlgus8648/Linux_device_driver/tree/main/13_Sending_Signals)|---|
|[14. The Poll Callback in a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/14_The_Poll_Callback_in_LKM)|---|
|[15. Waitqueues in a Linux Kerenl Module](https://github.com/dlgus8648/Linux_device_driver/tree/main/15_Waitqueues_in_LKM)|-process<br>scheduling|
|[16_Mutex](https://github.com/dlgus8648/Linux_device_driver/tree/main/16_Mutex)|-mutex, sempahore, spinlock, seqlock|
|[17_Misc](https://github.com/dlgus8648/Linux_device_driver/tree/main/17_Misc)|---|
|[18_dt_probe](https://github.com/dlgus8648/Linux_device_driver/tree/main/18_dt_probe)|-Device tree<br>probe()<br>platform_driver()|
|[19_DMA](https://github.com/dlgus8648/Linux_device_driver/tree/main/19_DMA)|-Completion<br>DMA|
|[20_Kobject](https://github.com/dlgus8648/Linux_device_driver/tree/main/20_Kobject)|-sysfs<br>참조카운트<br>kset|




