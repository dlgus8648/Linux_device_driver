
## 디바이스 파일과 디바이스 드라이버 등록

### 1. 디바이스 파일 (Device File)

디바이스 파일은 Linux 운영 체제에서 하드웨어 장치나 가상 장치를 나타내는 파일입니다. 이러한 파일은 일반적으로 `/dev` 디렉토리에 위치하며, 사용자 공간 프로그램이 커널 공간의 디바이스 드라이버와 통신할 수 있게 해줍니다. 디바이스 파일을 통해 사용자는 하드웨어 장치에 접근하고 제어할 수 있습니다.

### 2. 디바이스 번호

디바이스 파일은 주번호(major number)와 부번호(minor number)로 식별됩니다.

- **주번호 (Major Number)**: 디바이스와 연관된 드라이버를 식별합니다. 동일한 주번호를 여러 디바이스 드라이버가 공유할 수 있습니다.
- **부번호 (Minor Number)**: 드라이버가 개별 물리적 또는 논리적 장치를 구분하는 데 사용합니다.

### 3. 디바이스 드라이버 등록 및 디바이스 파일 생성

디바이스 드라이버를 등록하고 디바이스 파일을 생성하는 과정은 다음과 같습니다:

#### a) 디바이스 번호 할당

먼저 디바이스 번호를 할당받아야 합니다. 이는 두 가지 방법으로 가능합니다.

```c
// 디바이스 번호 수동할당
int register_chrdev_region(dev_t from, unsigned count, const char *name);

// 디바이스 번호 자동할당
int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
```

`register_chrdev_region`은 특정 주번호를 요청할 때 사용하고, `alloc_chrdev_region`은 동적으로 주번호를 할당받을 때 사용합니다[6].

#### b) 문자 디바이스 구조체 초기화 및 등록

다음으로 `cdev` 구조체를 초기화하고 시스템에 등록합니다[4]:

```c
cdev_init(&my_cdev, &my_fops);
cdev_add(&my_cdev, dev, 1);
```

#### c) 디바이스 클래스 생성

`class_create` 함수를 사용하여 디바이스 클래스를 생성합니다[7]:

```c
struct class *my_class = class_create("my_class");
```

#### d) 디바이스 파일 생성

마지막으로 `device_create` 함수를 사용하여 `/dev` 디렉토리에 실제 디바이스 파일을 생성합니다[7]:

```c
device_create(my_class, NULL, MKDEV(major, minor), NULL, "my_device");
```


---

# 실습 : 02_01 디바이스파일 생성방법(mknod 명령어)

![2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/68927307-634e-407a-9fe5-a947a62d4589)
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/8750263e-4988-4760-b5f0-6e2ae64580fe)
## 설명
"Device Numbers" 모듈은 문자 디바이스를 등록하고 주요 장치 번호(major device number)를 할당하는 리눅스 커널 모듈입니다.
이 예제는 `/dev` 디렉토리에 등록된 장치에 해당하는 디바이스 파일을 생성하는 방법과 커널 로그를 통해 등록 상태를 확인하는 방법을 시연합니다.

## 실행된 명령어
다음 명령어들은 디바이스 파일을 생성하고, 속성을 확인하며, 커널 로그 메시지를 확인하는 데 사용되었습니다:

1. `sudo mknod /dev/mydevice c 64 0`
   - 주요 번호 `64`와 부 번호 `0`을 가진 `mydevice`라는 이름의 디바이스 파일을 `/dev` 디렉토리에 생성합니다.
2. `ls /dev/mydevice -al`
   - `mydevice` 파일의 속성을 나열하여 생성 여부와 속성을 확인합니다.
3. `dmesg | tail -2`
   - 커널 로그 버퍼에서 마지막 두 개의 메시지를 표시하여 디바이스 등록 상태를 확인합니다.

## 커널 로그 메시지 및 /dev 디렉토리 출력
아래는 커널 로그 메시지와 `/dev` 디렉토리 출력에 대한 설명입니다:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ ls /dev/mydevice -al
crw-r--r-- 1 root root 64, 0 Jun 30 01:21 /dev/mydevice
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ ^C
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ dmesg | tail -2
[  390.169717] Hello, Kernel!
[  390.169731] dev_nr - registered Device number Major: 64, Minor: 0
```

### 상세 설명
1. `ls /dev/mydevice -al`
   - 이 명령은 `mydevice` 파일의 세부 정보를 나열하며, 해당 파일의 권한, 소유자, 그룹, 주요/부 번호를 보여줍니다.

2. `dmesg | tail -2`
   - 이 명령은 커널 로그의 마지막 두 개 메시지를 표시합니다. 이 메시지를 통해 장치가 커널에 성공적으로 등록되었는지 확인할 수 있습니다.

### 출력 설명
- `crw-r--r-- 1 root root 64, 0 Jun 30 01:21 /dev/mydevice`
   - `/dev/mydevice`: 디바이스 파일의 이름과 경로를 나타냅니다.

- `[90342.480445] Hello, Kernel!`
   - 이 메시지는 모듈이 초기화될 때 기록된 메시지로, 모듈이 성공적으로 로드되었음을 나타냅니다.

- `[90342.480492] dev_nr - registered Device number Major: 64, Minor: 0`
   - 이 메시지는 주요 번호 `64`와 부 번호 `0`을 가진 `dev_nr` 디바이스가 성공적으로 등록되었음을 확인해 줍니다.

## 결론
위의 단계와 출력은 "Device Numbers" 커널 모듈이 올바르게 작동함을 확인해 줍니다. 이 모듈은 주요 장치 번호 `64`와 함께 `my_dev_nr`라는 문자 디바이스를 성공적으로 등록했으며, 이 등록 상태는 `/dev` 디렉토리에 디바이스 파일을 생성하고 커널 로그 메시지를 확인하여 검증할 수 있습니다.

이 실습은 리눅스 커널 모듈에서 디바이스 번호와 디바이스 파일을 관리하는 방법을 이해하는 데 도움을 주며, 사용자 정의 장치를 생성하고 다루는 데 필요한 기초를 제공합니다.

---

# 02_02 디바이스 파일과 사용자프로그램의 상호작용


![4](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/d2af0aa5-09c2-4d5f-95fc-b2257999f7b6)
![5](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/e225dd40-8c82-4889-a5a9-70f1ccab8b93)
## 설명
"Device Numbers" 모듈은 문자 디바이스를 등록하고 주요 장치 번호(major device number)를 할당하는 리눅스 커널 모듈입니다. 이 예제는 `/dev` 디렉토리에 등록된 장치에 해당하는 디바이스 파일을 생성하고, 파일 권한을 수정하며, 테스트 프로그램을 사용해 해당 파일과 상호작용하는 방법을 시연합니다.

## 실행된 명령어
다음 명령어들은 디바이스 파일을 생성하고, 속성을 확인하며, 권한을 수정하고, 커널 로그 메시지를 확인하는 데 사용되었습니다:

1. `sudo mknod /dev/mydevice c 64 0`
   - 주요 번호 `64`와 부 번호 `0`을 가진 `mydevice`라는 이름의 디바이스 파일을 `/dev` 디렉토리에 생성합니다.
2. `sudo chmod 666 /dev/mydevice`
   - `mydevice` 파일의 권한을 수정하여 모든 사용자에게 읽기 및 쓰기 권한을 부여합니다.
3. `./test`
   - 테스트 프로그램을 실행하여 디바이스 파일을 열고 닫습니다.
4. `dmesg | tail -4`
   - 커널 로그 버퍼에서 마지막 네 개의 메시지를 표시하여 장치와의 상호작용을 확인합니다.

## 커널 로그 메시지 및 /dev 디렉토리 출력
아래는 커널 로그 메시지와 `/dev` 디렉토리 출력에 대한 설명입니다:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ sudo chmod 666 /dev/mydevice
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ ./test
Opening was successful!
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ dmesg | tail -4
[  390.169717] Hello, Kernel!
[  390.169731] dev_nr - registered Device number Major: 64, Minor: 0
[  904.880485] dev_nr - open was called!
[  904.880798] dev_nr - close was called!
```

### 상세 설명
1. `sudo chmod 666 /dev/mydevice`
   - 이 명령은 `mydevice` 파일의 권한을 `rw-rw-rw-`로 변경하여 소유자, 그룹, 다른 사용자 모두에게 읽기 및 쓰기 권한을 부여합니다.

2. `./test`
   - 이 명령은 테스트 프로그램을 실행하여 `mydevice` 파일을 열고 닫는 작업을 수행합니다. `Opening was successful!` 메시지는 테스트 프로그램이 디바이스 파일을 성공적으로 열었음을 나타냅니다.

3. `dmesg | tail -4`
   - 이 명령은 커널 로그의 마지막 네 개 메시지를 표시합니다. 이 메시지들은 모듈의 초기화 및 디바이스 파일과의 상호작용을 확인할 수 있습니다.

### 출력 설명
- `[90342.480445] Hello, Kernel!`
   - 이 메시지는 모듈이 초기화될 때 기록된 메시지로, 모듈이 성공적으로 로드되었음을 나타냅니다.

- `[90342.480492] dev_nr - registered Device number Major: 64, Minor: 0`
   - 이 메시지는 주요 번호 `64`와 부 번호 `0`을 가진 `dev_nr` 디바이스가 성공적으로 등록되었음을 확인해 줍니다.

- `[90542.893823] dev_nr - open was called!`
   - 이 메시지는 테스트 프로그램이 디바이스 파일을 열 때 기록된 것으로, 디바이스 드라이버의 `open` 함수가 호출되었음을 나타냅니다.

- `[90542.894195] dev_nr - close was called!`
   - 이 메시지는 테스트 프로그램이 디바이스 파일을 닫을 때 기록된 것으로, 디바이스 드라이버의 `close` 함수가 호출되었음을 나타냅니다.

## 결론
위의 단계와 출력은 "Device Numbers" 커널 모듈이 올바르게 작동함을 확인해 줍니다. 이 모듈은 주요 장치 번호 `64`와 함께 `my_dev_nr`라는 문자 디바이스를 성공적으로 등록했으며, 이 등록 상태는 `/dev` 디렉토리에 디바이스 파일을 생성하고, 파일 권한을 수정하며, 테스트 프로그램을 통해 디바이스 파일과 상호작용함으로써 검증할 수 있습니다.

이 실습은 리눅스 커널 모듈에서 디바이스 번호와 디바이스 파일을 관리하는 방법을 이해하는 데 도움을 주며, 사용자 정의 장치를 생성하고 다루는 데 필요한 기초를 제공합니다.

---
