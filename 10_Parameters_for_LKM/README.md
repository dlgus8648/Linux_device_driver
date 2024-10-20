# 10_Parameters_for_LKM


### DEMO

**1. 컴파일 및 모듈 로딩**

![제목 없음](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6ea9f9af-9d7c-443a-8c68-8625ff994bda)

   - 첫 번째 명령어는 커널 모듈이 기본 매개변수를 설정하는 것을 보여줍니다.
   - (`gpio_nr = 12` 및 `device_name = testdevice`).





**2. 매개변수 변경 후 다시 로딩**

![제목 없음2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/170e117a-bd97-4476-89b1-a8dda6afa4a2)

   - 두 번째 명령어는 커널 모듈이 특정 매개변수로 로드되는 것을 보여줍니다.
   - (`device_name="dummy"` 및 `gpio_nr=2`).



### 요약
![3](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/0102f8cf-0888-486f-b682-8af0887306d3)

이 프로젝트는 `my_params.ko`라는 커널 모듈을 사용합니다.
- 이 모듈은 **두 개의 매개변수**를 허용합니다: `device_name` 및 `gpio_nr`.
- 각 매개변수는 모듈이 초기화될 때 커널에 의해 설정됩니다.
