# ioctl_example Module
## 1. 모듈 로딩 및 초기화 메시지:

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/c18b2dab-102c-4937-8840-219ff8a1db57)

모듈이 초기화된 후 커널은 "Hello, Kernel!" 메시지를 출력하여 초기화가 성공적으로 이루어졌음을 나타냅니다.  
모듈은 등록된 장치 번호로 `주 번호 64`와 `부 번호 0`을 가지고 있음을 표시합니다.

## 2. 장치 노드 생성:

![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/7c987dc2-9369-46c3-ab9d-0c6f5c651953)

`/dev/dummy`라는 이름의 장치 노드가 `주 번호 64`와 `부 번호 0`으로 생성되었습니다.  
이 노드는 `ioctl_example` 모듈과 상호작용할 수 있는 인터페이스를 제공합니다.

## 3. 사용자 공간 프로그램 실행 및 결과 확인:

![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6702fb92-8d94-4679-a1b1-da30092c1857)

사용자 공간에서 실행된 `./test` 프로그램이 `ioctl_example` 모듈과 상호작용합니다.  
첫 번째 메시지는 기본 응답 값인 42를 출력합니다.  
두 번째 메시지는 응답 값이 123으로 업데이트되었음을 나타냅니다.  
장치가 성공적으로 열렸다는 메시지가 표시됩니다.

## 4. 커널 메시지 확인:

![4](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/054508a1-4398-49b3-b58b-8f3ebb6e3779)

커널 메시지 로그를 확인하여 모듈의 동작 및 상태를 검증합니다.
