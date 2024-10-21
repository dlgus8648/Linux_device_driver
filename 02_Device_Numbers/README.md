
# 02_Device Numbers Kernel Module

### 1. 디바이스 파일 (Device File)
디바이스 파일은 커널의 하드웨어 장치나 가상 장치를 나타내는 특별한 유형의 파일입니다. 
디바이스 파일을 사용하여 사용자는 하드웨어 장치에 접근할 수 있습니다.


### 2. 디바이스 파일 생성 방법
디바이스 파일은 보통 `/dev` 디렉토리에 위치하며, 이 실습에서는 2가지 방법으로 디바이스 파일을 생성하는 실습을 진행했습니다.
- 드라이버 코드에서 디바이스 파일을 생성하는 방법 `register_chrdev()`
- 사용자 터미널에서 디바이스 파일을 생성하는 방법 `mknod 명령어`

디바이스 파일은 주번호와 부번호로 특정됩니다. 이를 통해 커널은 주번호를 통해 해당 디바이스 파일이 어떤 드라이버가 그 파일을 처리해야 하는지 알아냅니다. 
일반적으로 리눅스 커널에는 이미 여러 주번호가 예약되어 있으며, 주요 하드웨어 장치나 가상 장치에 할당되어 있습니다.
사용자는 자신이 작성한 드라이버에 고유한 주번호를 할당하거나, 커널에 의해 자동 할당(실습3_Auto_Device_file_Creation)되도록 할 수 있습니다.



# 02_01 디바이스 파일 생성방법(register_chrdev())
![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/a628118c-a8d1-4553-a622-28000e6cf2ee)
## 설명
"Device Numbers" 모듈은 문자 디바이스를 등록하고 주요 장치 번호(major device number)를 할당하는 리눅스 커널 모듈입니다. 
이 예제는 커널에서 디바이스 번호를 다루는 방법을 실습합니다.
``retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);``로 MYMAJOR번호를 64로 지정하고 my_dev_nr이라는 디바이스파일을 생성합니다.

## 실행된 명령어
다음 명령어는 모듈을 삽입하고 등록 상태를 확인하는 데 사용되었습니다:

1. `sudo insmod dev_nr.ko`
   - 커널 모듈을 커널에 삽입합니다.
2. `cat /proc/devices | grep my_dev_nr`
   - 등록된 장치 목록을 표시하고, `my_dev_nr` 항목을 보여주도록 필터링합니다.

## 커널 로그 메시지 및 /proc/devices 출력
아래는 커널 로그 메시지와 `/proc/devices` 출력에 대한 설명입니다:

```
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ sudo insmod dev_nr.ko
kim@kimrihyeon:~/Linux_device_driver/02_Device_Numbers$ cat /proc/devices | grep my_dev_nr
 64 my_dev_nr
```

### 상세 설명
1. `sudo insmod dev_nr.ko`
   - 이 명령은 커널 모듈 `dev_nr.ko`를 커널에 삽입합니다. 모듈의 초기화 함수가 실행되어, 특정 주요 장치 번호와 함께 문자 디바이스가 등록됩니다.
   
2. `cat /proc/devices | grep my_dev_nr`
   - `/proc/devices` 파일은 시스템에 등록된 모든 문자 및 블록 디바이스 목록과 그들의 주요 장치 번호를 포함합니다. `grep my_dev_nr` 명령어를 사용하여, 해당 디바이스의 항목을 필터링하여 찾습니다.

### 출력 설명
- `64 my_dev_nr`
  - 이 줄은 `my_dev_nr`라는 이름의 디바이스가 주요 장치 번호 `64`로 성공적으로 등록되었음을 나타냅니다. 주요 번호는 `my_dev_nr`와 연결된 디바이스 드라이버를 고유하게 식별합니다.

## 결론
위의 단계와 출력은 "Device Numbers" 커널 모듈이 올바르게 작동함을 확인해 줍니다. 이 모듈은 `my_dev_nr`라는 문자 디바이스를 주요 장치 번호 `64`와 함께 성공적으로 등록했으며, 이 등록은 `/proc/devices` 파일을 통해 확인할 수 있습니다.

이 실습은 리눅스 커널 모듈에서 디바이스 번호를 관리하는 방법을 이해하는 데 도움이 되며, 사용자 정의 장치를 만들고 다루는 데 필요한 기초를 제공합니다.

---

# 02_02 디바이스파일 생성방법(mknod 명령어)

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

# 02_03 디바이스 파일과 사용자프로그램의 상호작용


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
