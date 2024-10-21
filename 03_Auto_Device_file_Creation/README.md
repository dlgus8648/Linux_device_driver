
# 03_Auto_Device_file_Creation

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/e1d54135-1c07-43d3-a42e-27c2ed2f7591)
## 설명

이번 실험은 `read_write.ko` 커널 모듈을 로드하여 자동으로 디바이스 파일을 생성하고, 그 파일이 `/dev` 디렉토리에 정상적으로 생성되었는지 확인하는 것을 목표로 하였다. 디바이스 파일은 유저 공간과 커널 공간 사이에서 데이터를 교환하기 위한 중요한 인터페이스이며, 본 실험에서는 커널 모듈이 이러한 디바이스 파일을 자동으로 생성하는 과정을 확인하였다.


1. **커널 모듈 삽입**: `sudo insmod read_write.ko` 명령어를 사용하여 `read_write.ko` 커널 모듈을 커널에 삽입하였다. 이 커널 모듈은 자동으로 디바이스 파일을 생성하는 코드가 포함되어 있다.
   
2. **디바이스 파일 확인**: `ls /dev/dummydriver` 명령어를 사용하여 `/dev` 디렉토리 내에 `dummydriver`라는 이름의 디바이스 파일이 자동으로 생성된 것을 확인할 수 있다.

`read_write.ko` 모듈을 커널에 로드한 후 `/dev/dummydriver`라는 디바이스 파일이 자동으로 생성되었다. 이를 통해 커널 모듈이 유저 공간에서 사용할 수 있는 디바이스 파일을 정상적으로 생성함을 알 수 있다.




3. **Set Device File Permissions**
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/fed19da1-6247-4a11-9bb1-d485eae7e86b)

### 설명

이번 실습에서는 `/dev/dummydriver` 디바이스 파일에 대한 권한을 수정하고, 데이터를 쓰고 읽는 작업을 수행하였다. `echo`와 `head` 명령어를 사용하여 디바이스 파일에 데이터를 작성하고, 그 데이터를 올바르게 읽을 수 있는지 확인하는 과정이었다.

1. **디바이스 파일 권한 수정**: 
   - 디바이스 파일의 읽기 및 쓰기 권한을 모든 사용자에게 부여하기 위해 `chmod` 명령어를 사용하였다.
   - 명령어: `sudo chmod 666 /dev/dummydriver`

2. **디바이스 파일에 데이터 쓰기**:
   - `echo` 명령어를 사용하여 디바이스 파일에 문자열 "This is a test"를 작성하였다.
   - 명령어: `echo "This is a test" > /dev/dummydriver`

3. **디바이스 파일에서 데이터 읽기**:
   - `head` 명령어를 사용하여 디바이스 파일의 첫 번째 줄을 읽었다. 작성된 데이터가 올바르게 저장되었는지 확인하였다.
   - 명령어: `head -n 1 /dev/dummydriver`

4. **추가 데이터 쓰기**:
   - `echo` 명령어를 사용하여 디바이스 파일에 "KIMRIHYEON"이라는 추가 데이터를 작성하였다.
   - 명령어: `echo "KIMRIHYEON" > /dev/dummydriver`

5. **여러 줄 읽기**:
   - `head` 명령어로 디바이스 파일의 첫 번째와 두 번째 줄을 읽어, 데이터를 올바르게 기록하고 유지하는지 확인하였다.
   - 명령어: `head -n 2 /dev/dummydriver`

- 첫 번째 `echo "This is a test"` 명령어로 데이터를 작성한 후 `head -n 1` 명령어로 읽은 결과, **"This is a test"**가 출력되었다.
- 그 후, `echo "KIMRIHYEON"` 명령어로 추가 데이터를 작성한 후 `head -n 2` 명령어로 두 줄을 읽은 결과, 두 줄 모두 **"KIMRIHYEON"**이라는 내용으로 출력되었다.

이 결과는 데이터가 이전에 작성된 내용을 덮어쓰는 방식으로 처리되었음을 나타낸다. 즉, 마지막에 작성된 "KIMRIHYEON"이 첫 번째 줄을 포함한 모든 데이터를 덮어썼으며, 이로 인해 두 줄 모두 "KIMRIHYEON"이라는 동일한 데이터가 출력되었다.

