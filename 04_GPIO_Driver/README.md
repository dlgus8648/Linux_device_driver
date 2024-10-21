# GPIO 디바이스 드라이버 제어 실습 

### GPIO Control using /sys/class/gpio:
![2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/0735da6a-5d7b-4eaa-af89-a3887d92b024)

### GPIO Control using /sys/class/gpio_blink:
https://github.com/dlgus8648/Linux_device_driver/assets/139437162/83652677-ffec-42e9-a2c8-1d1932d4051f


#### 1. 설명
이번 실습에서는 주어진 GPIO 디바이스 드라이버 코드를 기반으로 리눅스 커널 모듈을 작성하고, 이를 통해 GPIO 핀을 제어하는 방법을 실습하였다. 
실습 대상 핀은 Raspberry Pi의 GPIO 21번 핀이며, 이 핀에 대한 읽기 및 쓰기 동작을 /sys/class/gpio로 수행하여, 제어와 상태 확인이 가능함을 확인하는 것을 목표로 한다.

#### 2. 코드
이 실습에서는 다음과 같은 주요 기능이 포함된 GPIO 디바이스 드라이버 코드를 작성하였다.

1. **GPIO 핀 정의 및 디바이스 드라이버 등록**:
   - GPIO 21번 핀을 사용하기 위해 `GPIO_21` 매크로를 정의하고, 커널 모듈에서 해당 핀에 대한 제어를 수행한다.
   - `alloc_chrdev_region()` 함수를 통해 디바이스 번호를 할당하고, `cdev_init()`으로 `file_operations` 구조체를 초기화하여 디바이스 파일과 드라이버 간의 상호작용을 설정한다.
   - `device_create()` 함수를 통해 `/dev/gpio_device`라는 디바이스 파일을 생성하여, 유저 공간에서 이 파일을 통해 GPIO 핀에 접근할 수 있도록 한다.

2. **GPIO 핀의 읽기 동작**:
   - `gpio_read()` 함수는 `gpio_get_value(GPIO_21)`를 사용하여 GPIO 21번 핀의 상태(0 또는 1)를 읽어와 사용자에게 전달한다.
   - 이 함수는 `copy_to_user()` 함수를 통해 읽은 값을 유저 공간으로 전달한다. 읽은 값은 핀의 현재 상태이며, 이를 통해 해당 핀의 전압이 LOW인지 HIGH인지를 확인할 수 있다.

3. **GPIO 핀의 쓰기 동작**:
   - `gpio_write()` 함수는 사용자가 입력한 데이터를 기반으로 핀의 상태를 설정한다.
   - 입력 값이 '1'이면 GPIO 핀을 HIGH로 설정하고, '0'이면 LOW로 설정한다.
   - 이는 `gpio_set_value(GPIO_21, 1)` 또는 `gpio_set_value(GPIO_21, 0)`을 호출하여 핀의 출력을 제어한다.

4. **드라이버 초기화 및 종료**:
   - `gpio_driver_init()` 함수는 드라이버 초기화 시 호출되며, 디바이스 파일을 생성하고 GPIO 핀을 요청하여 출력 방향으로 설정한다.
   - `gpio_driver_exit()` 함수는 드라이버가 언로드될 때 호출되며, GPIO 핀을 해제하고 관련된 리소스들을 정리한다.

#### 3. 실습 절차

1. **커널 모듈 컴파일 및 삽입**:
   - 작성한 `gpio_driver` 커널 모듈 코드를 컴파일한 후, `sudo insmod gpio_driver.ko` 명령어로 커널에 모듈을 삽입하였다.
   - 모듈이 삽입되면 `/dev/gpio_device`라는 디바이스 파일이 자동으로 생성되며, 이를 통해 GPIO 21번 핀에 대한 읽기 및 쓰기 작업을 수행할 수 있다.

2. **GPIO 상태 읽기**:
   - `cat /dev/gpio_device` 명령어를 사용하여 GPIO 21번 핀의 상태를 읽었다.
   - 핀이 LOW 상태일 때는 '0', HIGH 상태일 때는 '1'이 출력된다.
   - 드라이버는 `gpio_read()` 함수에서 `gpio_get_value()`를 통해 현재 핀의 상태를 읽고, 이를 유저 공간으로 전달한다.

3. **GPIO 상태 쓰기**:
   - `echo "1" > /dev/gpio_device` 명령어로 GPIO 핀을 HIGH 상태로 설정하고, `echo "0" > /dev/gpio_device` 명령어로 LOW 상태로 변경하였다.
   - 드라이버의 `gpio_write()` 함수는 유저로부터 전달받은 값을 기반으로 `gpio_set_value()`를 호출하여 핀의 출력을 제어하였다.

#### 4. 실습 결과

1. **커널 모듈 로드 성공**:
   - `gpio_driver.ko` 모듈을 성공적으로 커널에 로드하였다. `dmesg` 명령어를 통해 커널 로그를 확인한 결과, 모듈이 정상적으로 초기화되었으며 `/dev/gpio_device` 파일이 생성된 것을 확인하였다.

2. **GPIO 핀 읽기 및 쓰기 동작 성공**:
   - GPIO 21번 핀의 상태를 읽고, 유저 공간에서 핀을 제어하는 작업이 성공적으로 이루어졌다. `cat /dev/gpio_device`를 통해 핀 상태를 읽을 수 있었으며, `echo "1" > /dev/gpio_device`를 통해 핀을 HIGH로 설정할 수 있었다.

3. **에러 처리**:
   - 드라이버 코드에서 예상치 못한 입력이 들어올 경우, `gpio_write()` 함수에서 "unknown command"라는 에러 메시지를 출력하도록 구현하였다. 이는 입력 값이 '0'이나 '1'이 아닌 경우에 발생하는 에러로, 잘못된 입력을 처리하는 방식이 정상적으로 작동함을 확인하였다.

