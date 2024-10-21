
# Linux Kernel Module: Kthread Example
이 리눅스 커널 모듈(LKM)은 간단한 예제를 통해 커널 스레드(kthread)의 사용법을 보여줍니다. 이 모듈은 두 개의 커널 스레드를 생성하여 각각의 카운터를 증가시키고, 해당 활동을 커널 로그에 기록합니다.

## 설명

이 예제는 리눅스 커널 모듈 내에서 커널 스레드를 생성하고 관리하는 방법을 설명합니다.

- kthread 1은 1초마다 실행됩니다.
- kthread 2는 2초마다 실행됩니다.

## 커널 로그 출력

다음은 모듈을 로드한 후 kthread의 동작을 관찰한 커널 로그의 샘플 출력입니다:

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/a8af8cb0-1f3a-4512-9faa-0b6a81d9b496)


