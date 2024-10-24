# 17_Misc_Device.

## 관련개념

**MISC (Miscellaneous) 디바이스**는 **리눅스 커널**에서 **주 번호(major number)** 소진 문제를 해결하기 위해 도입된 특별한 장치 클래스입니다.
MISC 디바이스는 다양한 기능을 하는 장치들을 한 곳에서 관리하기 위한 구조로, 특정한 범주에 속하지 않는 장치들이 주로 이 카테고리에 속합니다.

### 1. **주 번호 소진 문제**
리눅스 시스템에는 사용할 수 있는 **주 번호가 제한적**입니다. 리눅스 커널은 주 번호를 **8비트 또는 12비트**로 관리하는데, 이는 **255개 또는 4095개의 장치 드라이버**에 할당할 수 있다는 의미입니다. 하지만 시간이 지나면서 새로운 장치가 계속 추가되면서 **주 번호가 부족**해지는 문제가 발생할 수 있습니다.

- 리눅스 시스템이 커지면서 다양한 디바이스 드라이버가 커널에 추가되는데, 주 번호가 한정적이므로 많은 장치에 대해 번호를 할당하는 것이 어려워질 수 있습니다.

### 2. **MISC 디바이스의 도입**
이러한 **주 번호 소진 문제**를 해결하기 위해 리눅스 커널은 **MISC 디바이스**라는 개념을 도입했습니다. MISC 디바이스는 **주 번호 10**을 사용하며, 여러 종류의 장치를 **부 번호(minor number)**로 관리하는 방식입니다. 즉, MISC 디바이스를 통해 다양한 장치를 **하나의 주 번호**로 처리할 수 있게 되어, 주 번호 소진 문제를 해결합니다.

### 3. **MISC 디바이스의 구조와 동작**
- **주 번호 10**: 모든 MISC 디바이스는 동일한 **주 번호 10**을 공유합니다. 이 주 번호를 통해 다양한 기타 장치들이 하나의 범주에 포함됩니다.
- **부 번호**: MISC 디바이스의 실제 장치는 **부 번호**로 구분됩니다. 커널은 각 MISC 디바이스에 **다른 부 번호**를 부여하여 이를 식별합니다.
 .

### 4. **사용예시**
MISC 디바이스는 일반적으로 **misc_register()** 함수를 사용하여 리눅스 커널에 등록됩니다. 이 함수는 주 번호 10에 해당하는 MISC 디바이스를 부 번호와 함께 등록하는 역할을 합니다.
이 코드는 **Linux 커널**에서 **MISC 디바이스**를 등록하고, 파일 입출력 기능을 제공하는 간단한 **디바이스 드라이버**입니다. 주로 `misc_register()`와 `misc_deregister()` 함수가 사용되며, 디바이스 파일을 통해 데이터를 읽고 쓰는 작업을 처리합니다. 이제 이 코드에서 **MISC 디바이스** 관련 함수들과 **파일 입출력** 함수들이 어떻게 쓰였는지 자세히 설명하겠습니다.

### 1. **MISC 디바이스 등록 및 해제 관련 함수**

#### 1) **misc_register() 함수**
```c
status = misc_register(&my_device);
```
이 함수는 MISC 디바이스를 커널에 등록하는 역할을 합니다. 코드를 보면, `my_device`라는 **구조체**가 MISC 디바이스로 등록됩니다. 이 구조체는 **디바이스 이름**, **부 번호(minor number)**, **파일 연산자(file operations)** 정보를 포함합니다.

- `name`: `"testdev"`로 설정되어 있으며, 이는 `/dev/testdev`라는 장치 파일로 나타납니다.
- `minor`: `MISC_DYNAMIC_MINOR`를 사용하여 동적으로 부 번호를 할당받습니다.
- `fops`: **파일 연산자**로, 디바이스 파일에서 수행할 수 있는 동작(읽기, 쓰기, 열기, 닫기)을 정의한 구조체입니다.

MISC 디바이스를 등록하면, **커널**은 `/dev/` 디렉토리에 장치 파일을 생성하고 이를 통해 사용자 공간에서 해당 디바이스를 사용할 수 있게 됩니다. 이 장치 파일은 유저 공간과 커널 간의 인터페이스로 작동합니다.

#### 2) **misc_deregister() 함수**
```c
misc_deregister(&my_device);
```
이 함수는 `misc_register()`로 등록된 MISC 디바이스를 **해제**하는 역할을 합니다. 모듈이 언로드 될 때 이 함수를 호출하여 디바이스 파일(`/dev/testdev`)을 커널에서 제거하고 더 이상 접근할 수 없게 만듭니다.

### 3. **MISC 디바이스 파일 구조체 설정**
```c
static struct miscdevice my_device = {
	.name = "testdev",
	.minor = MISC_DYNAMIC_MINOR,
	.fops = &fops,
};
```
- 이 구조체는 MISC 디바이스로 **등록될 장치**를 정의합니다.
- `name`: `"testdev"`으로 설정되어 있으므로 `/dev/testdev`로 장치 파일이 생성됩니다.
- `minor`: `MISC_DYNAMIC_MINOR`을 사용하므로 **동적 부 번호**가 할당됩니다. 즉, 커널이 자동으로 사용할 수 있는 부 번호를 할당합니다.
- `fops`: **파일 연산자 구조체**를 지정하여 장치 파일에서 호출할 함수를 정의합니다.



## Demo
![misc](https://github.com/user-attachments/assets/1b1e336a-b4cc-411b-81fe-c1382c30a5ef)


## C. 코드 구현

이 코드는 `misc` 디바이스를 생성하여 간단한 읽기/쓰기를 지원하는 Linux 커널 모듈입니다. `misc` 디바이스는 주로 소규모 장치에서 사용되는 장치로, 문자 디바이스를 간편하게 관리할 수 있도록 해줍니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`my_init` 호출)
   - `module_init()` 매크로에 의해 **my_init** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **misc_register()** 호출
   - **`misc` 디바이스 등록**: `misc_register()` 함수는 `my_device` 구조체로 정의된 `misc` 디바이스를 커널에 등록합니다. 
   - 이 `misc` 디바이스는 `/dev/testdev`라는 이름을 가지며, `fops`에 정의된 파일 작업들을 지원합니다.
   - 등록에 성공하면 "misc_test - Register misc device" 메시지를 출력하고, 실패 시 에러 메시지를 출력하고 함수가 종료됩니다.

### 2. 디바이스 파일 조작 시 (열기, 읽기, 쓰기, 닫기)

#### 2-1. **my_open()** 호출
   - **디바이스 파일 열기**: 사용자 애플리케이션에서 디바이스 파일(`/dev/testdev`)을 열 때 `my_open()` 함수가 호출됩니다.
   - 이 함수는 열리는 파일이 읽기 권한으로 열렸는지, 쓰기 권한으로 열렸는지에 대한 정보를 로그에 기록합니다.
   - "misc_test - Open called" 메시지를 출력하고 성공적으로 열렸다는 메시지를 출력합니다.

#### 2-2. **my_write()** 호출
   - **디바이스 파일에 쓰기**: 사용자 애플리케이션에서 디바이스 파일에 데이터를 쓸 때 `my_write()` 함수가 호출됩니다.
   - `copy_from_user()` 함수를 사용해 사용자 공간의 데이터를 커널 공간에 있는 `data` 배열로 복사합니다.
   - 쓰기 요청이 완료되면 "misc_test - Write called" 메시지가 출력됩니다. `copy_from_user()`에서 에러가 발생하면 에러 메시지를 출력하고, 에러 값을 반환합니다.

#### 2-3. **my_read()** 호출
   - **디바이스 파일에서 읽기**: 사용자 애플리케이션에서 디바이스 파일에서 데이터를 읽을 때 `my_read()` 함수가 호출됩니다.
   - `copy_to_user()` 함수를 사용해 커널 공간에 있는 `data` 배열의 데이터를 사용자 공간으로 복사합니다.
   - 읽기 요청이 완료되면 "misc_test - Read called" 메시지를 출력합니다. `copy_to_user()`에서 에러가 발생하면 에러 메시지를 출력하고, 에러 값을 반환합니다.

#### 2-4. **my_close()** 호출
   - **디바이스 파일 닫기**: 사용자 애플리케이션이 디바이스 파일을 닫을 때 `my_close()` 함수가 호출됩니다.
   - "misc_test - Close called" 메시지를 출력하고 파일이 정상적으로 닫혔다는 로그를 기록합니다.

### 3. 모듈 언로드 시 (`my_exit` 호출)
   - `module_exit()` 매크로에 의해 **my_exit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **misc_deregister()** 호출
   - **`misc` 디바이스 해제**: `misc_deregister()` 함수는 등록된 `misc` 디바이스를 시스템에서 해제합니다. 
   - 이 함수는 `/dev/testdev` 파일을 시스템에서 제거하여 더 이상 접근할 수 없도록 합니다.

### 함수 호출 순서 요약

1. **my_init()** → 모듈 로드, `misc` 디바이스 등록
   - `misc_register()`로 `/dev/testdev` 디바이스 등록

2. **my_open()**, **my_write()**, **my_read()**, **my_close()** → 디바이스 파일 조작
   - `my_open()` → 디바이스 파일 열기
   - `my_write()` → 사용자 공간 데이터를 커널 공간으로 복사
   - `my_read()` → 커널 공간 데이터를 사용자 공간으로 복사
   - `my_close()` → 디바이스 파일 닫기

3. **my_exit()** → 모듈 언로드, `misc` 디바이스 해제
   - `misc_deregister()`로 `/dev/testdev` 디바이스 해제

이 순서는 `misc` 디바이스가 로드되고 사용자 애플리케이션과 상호작용하며, 이후 모듈이 언로드되는 과정을 설명합니다.
