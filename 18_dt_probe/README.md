# 18_dt_probe

## 관련개념
**Device Tree**, **probe() 함수**, **platform_driver()**는 모두 **임베디드 시스템**이나 **리눅스 커널**에서 하드웨어 장치와 소프트웨어 간의 상호작용을 처리하는데 중요한 개념들입니다. 이들 개념의 도입 배경을 설명하면서, 각각이 어떻게 하드웨어 장치 관리 문제를 해결하는지 자세히 설명하겠습니다.

---

### 1. **Device Tree (디바이스 트리)**

#### **도입 배경**
기존의 **하드웨어 초기화 방식**은 커널 코드에 직접적으로 하드웨어 관련 정보를 포함하는 방식이었습니다. 이는 다음과 같은 문제들을 발생시켰습니다:
- **하드웨어 종속성**: 커널 코드에 특정 하드웨어 플랫폼에 대한 정보가 직접 하드코딩되었기 때문에, 하드웨어를 변경하거나 새로운 플랫폼을 지원하려면 커널 자체를 수정해야 했습니다.
- **유연성 부족**: 다양한 하드웨어 플랫폼에서 동일한 커널을 사용하는 것이 어려웠습니다. 커널이 하드웨어에 대해 알고 있어야 했고, 새로운 장치나 변경 사항을 지원하기 위해 커널을 자주 수정해야 했습니다.

이러한 문제를 해결하기 위해 **디바이스 트리(Device Tree)** 가 도입되었습니다. 디바이스 트리는 **하드웨어의 구성 정보를 외부 파일**로 분리하여, 커널이 특정 하드웨어에 대한 정보를 미리 알지 않아도 하드웨어를 초기화할 수 있도록 합니다.
디바이스 트리는 **하드웨어를 설명하는 데이터 구조**입니다. 이 데이터 구조는 텍스트 형식으로 작성된 **Device Tree Source 파일(.dts)** 과 컴파일된 **Device Tree Blob(.dtb)** 파일로 존재하며, 이 파일을 통해 커널은 하드웨어 장치의 특성을 알게 됩니다.
이 디바이스 트리 파일(Device Tree Source, **.dts** 파일)은 **Raspberry Pi** 같은 **bcm2835** 기반의 시스템에서 **새로운 장치**를 정의하고 추가하는 예시입니다. 이 파일은 **하드웨어 장치의 속성**을 정의하고, 이를 운영체제(커널)에 전달하여 장치의 초기화를 돕는 역할을 합니다. 이제 이 디바이스 트리 파일의 각 구성 요소와 의미를 자세히 설명하겠습니다.

#### 1. **작동 흐름**

1. **디바이스 트리 로드**: 시스템이 부팅될 때, 이 디바이스 트리 파일이 읽히고, `compatible` 속성을 통해 **커널이 적합한 드라이버를 검색**합니다. 여기서는 `"brightlight,mydev"`라는 호환성을 가진 드라이버가 로드됩니다.
2. **장치 초기화**: 커널은 이 장치가 **status = "okay"** 로 설정되어 있기 때문에, 장치가 사용 가능함을 인식하고 **초기화** 작업을 수행합니다.
3. **드라이버와 연동**: 커널이 드라이버를 초기화하면서, `my_value`와 같은 속성 값들을 드라이버에서 사용하여 장치의 동작을 제어할 수 있게 됩니다.

#### 2. **파일 헤더**

```dts
/dts-v1/;
/plugin/;
```

- `/dts-v1/`: 디바이스 트리 소스 파일이 **버전 1 형식**임을 나타냅니다. 디바이스 트리의 형식이 여러 버전으로 나올 수 있는데, 이 파일은 첫 번째 버전 형식에 맞춰 작성된 것입니다.
  
- `/plugin/`: 이 파일은 디바이스 트리의 **플러그인**이라는 것을 나타냅니다. 플러그인은 기존 디바이스 트리의 일부를 **수정하거나 추가**하는 역할을 합니다. 이를 통해 기본적인 디바이스 트리에 특정 하드웨어 장치나 설정을 추가할 수 있습니다.

#### 3. **최상위 노드**

```dts
/ {
	compatible = "brcm,bcm2835";
	fragment@0 {
		target-path = "/";
		__overlay__ {
			my_device {
				compatible = "brightlight,mydev";
				status = "okay";
				label = "Test";
				my_value = <12>;
			};
		};
	};
};
```

#### **1) 최상위 노드 (`/`)**
- **/**: 루트 노드를 의미하며, 시스템의 최상위 노드를 나타냅니다. 이 노드는 전체 시스템 트리 구조의 **시작점**입니다.
  
#### **2) compatible = "brcm,bcm2835"**
- `compatible`: 이 노드는 해당 디바이스 트리가 **어떤 시스템과 호환되는지**를 나타냅니다.
  - `"brcm,bcm2835"`는 **Broadcom**의 **BCM2835 SoC**(System on Chip)를 나타내며, **Raspberry Pi** 모델이 주로 사용하는 SoC입니다. 이 SoC에서 동작하는 장치나 드라이버와의 호환성을 나타냅니다.

#### **3) fragment@0 노드**
- `fragment@0`: 디바이스 트리의 플러그인을 적용할 때 사용하는 **프래그먼트(fragment)** 노드입니다. 프래그먼트는 기존 디바이스 트리에 **부분적으로 변경** 또는 **추가되는 장치**를 나타냅니다.
  - 여기서는 `fragment@0`이라는 이름을 사용했으며, 여러 프래그먼트를 사용할 경우 숫자를 증가시키면서 여러 개의 프래그먼트를 정의할 수 있습니다.

#### **4) target-path = "/"**
- `target-path = "/"`: 이 속성은 **디바이스 트리에서 어느 위치에 이 프래그먼트를 적용할 것인지**를 나타냅니다. 여기서는 루트 노드 `/`에 적용된다는 것을 의미합니다. 즉, 시스템의 최상위 노드에 새로운 장치를 추가하거나 수정하는 것입니다.

### 3. **__overlay__ 노드**

#### **__overlay__**
- `__overlay__`: 플러그인의 **오버레이 섹션**입니다. 이는 기존의 디바이스 트리에 추가될 내용이 무엇인지 정의합니다. 오버레이는 디바이스 트리의 **일부를 덮어쓰기** 위해 사용됩니다.

#### **my_device 노드**
```dts
my_device {
	compatible = "brightlight,mydev";
	status = "okay";
	label = "Test";
	my_value = <12>;
};
```

- **my_device**: 오버레이 섹션에 정의된 **새로운 장치**입니다. 이 장치의 구체적인 속성은 다음과 같습니다.

1. **compatible = "brightlight,mydev"**: 이 장치가 어떤 **드라이버**나 **장치**와 호환되는지 나타냅니다.
   - `"brightlight,mydev"`는 새로운 장치의 **제조사**나 **장치 유형**을 나타내는 문자열입니다. 이 값을 통해 커널은 적절한 드라이버를 선택하여 장치에 매핑할 수 있습니다. 예를 들어, **"brightlight"**라는 제조사에서 만든 **"mydev"**라는 장치를 나타냅니다.
  
2. **status = "okay"**: 이 장치가 **활성화**되어 있음을 나타냅니다. 디바이스 트리에서 `status`는 장치의 상태를 정의하며, `"okay"`는 해당 장치가 **정상적으로 활성화**되어 사용할 수 있다는 의미입니다.
   - 다른 값으로는 `"disabled"`가 있는데, 이는 장치가 비활성화됨을 의미합니다.

3. **label = "Test"**: 이 장치의 **레이블**을 정의합니다. 이는 사용자나 개발자가 장치를 식별하기 위한 문자열로, 커널 내에서 장치를 식별하는 데 도움이 됩니다.

4. **my_value = <12>**: 장치의 **속성 값**을 나타냅니다. 이 값은 `my_device` 장치에 추가된 커스텀 속성으로, **정수형 값 12**를 나타냅니다. 이 속성은 디바이스 트리 내에서 드라이버가 참조할 수 있는 값입니다.


---

### 2. **probe() 함수**

임베디드 시스템에서는 장치들이 **플러그 앤 플레이(Plug and Play)** 방식으로 동적으로 감지되기 보다는, 시스템 부팅 시 이미 존재하는 장치들이 초기화됩니다. 이를 위해 커널은 특정 장치 드라이버가 해당 하드웨어 장치와 연결될 수 있도록 초기화하는 과정이 필요합니다. 이러한 과정에서 **probe() 함수**가 도입되었습니다.
`probe()` 함수는 **장치 드라이버가 특정 하드웨어 장치를 초기화**할 때 호출되는 함수입니다. 커널이 부팅되거나 장치가 등록될 때, 커널은 각 장치 드라이버의 `probe()` 함수를 호출하여 장치와 드라이버를 연결합니다.
- **하드웨어 장치의 존재 확인**: `probe()` 함수는 드라이버가 관리하는 장치가 실제로 존재하는지 확인합니다.
- **장치 초기화**: 하드웨어 장치의 자원(메모리, 인터럽트 등)을 할당하고, 드라이버와 장치를 연결합니다.
- **장치 등록**: 커널에 장치를 등록하여, 다른 커널 기능이나 사용자 공간 프로그램이 이 장치와 상호작용할 수 있도록 합니다.


---

### 3. **platform_driver()**

#### **도입 배경**
리눅스 커널에서는 하드웨어 장치에 따라 다양한 드라이버 인터페이스가 존재합니다. 그중에서도 **플랫폼 장치(platform device)** 는 주로 CPU나 SoC(System on Chip)와 관련된 장치들로, 이러한 장치를 처리하는 플랫폼 드라이버가 필요합니다. 플랫폼 장치는 일반적으로 **버스(bus)** 가 없기 때문에, 이를 관리하는 플랫폼 드라이버가 도입되었습니다.

#### **platform_driver()란?**
`platform_driver`는 **플랫폼 장치를 관리하는 드라이버 구조체**로, `probe()` 함수와 `remove()` 함수를 등록하여 특정 플랫폼 장치에 대해 드라이버가 동작하도록 합니다.

- **platform_device**: 플랫폼 장치는 별도의 버스 없이 직접적으로 메모리 매핑된 장치입니다. SoC에 내장된 장치들이 주로 플랫폼 장치로 처리됩니다.
- **platform_driver 구조체**: 해당 구조체는 플랫폼 장치와 연동되는 드라이버를 정의하며, **장치의 초기화**, **자원 할당**, **드라이버 제거** 등의 작업을 수행하는 콜백 함수들을 포함합니다.


이 코드는 **Linux 커널**에서 **platform driver**와 **device tree**를 이용하여 특정 장치의 속성을 읽어오는 **플랫폼 드라이버**입니다. **platform_driver()**와 관련된 코드가 어떻게 쓰였는지 자세히 설명하겠습니다.

---

### 1. **platform_driver와 관련된 개념**

- **Platform Driver**는 **버스(bus)**가 없는 장치를 처리하기 위한 드라이버로, 주로 **SoC**나 **임베디드 시스템**에서 CPU와 연결된 장치들을 관리합니다.
- 이 코드는 **Device Tree**를 통해 하드웨어 장치가 정의되고, 해당 장치에 맞는 드라이버가 동적으로 연결되는 구조입니다. 이 드라이버는 `probe()`와 `remove()` 함수를 통해 장치를 초기화하고, 제거할 때 관련된 작업을 처리합니다.

---

### 2. **platform_driver 구조체 정의**

```c
static struct platform_driver my_driver = {
	.probe = dt_probe,
	.remove = dt_remove,
	.driver = {
		.name = "my_device_driver",
		.of_match_table = my_driver_ids,
	},
};
```

이 부분은 **platform_driver 구조체**를 정의하는 코드입니다. 플랫폼 드라이버는 주로 다음과 같은 속성들을 정의합니다.

- **probe = dt_probe**: 이 드라이버가 해당 장치와 **연결될 때 호출**되는 함수입니다. 장치가 발견되면 커널은 `probe()` 함수를 호출하여 장치를 초기화합니다.
  
- **remove = dt_remove**: 장치가 시스템에서 제거되거나 드라이버가 언로드 될 때 호출되는 함수입니다. 이 함수는 장치와 관련된 자원을 정리하는 역할을 합니다.

- **driver = {...}**: `platform_driver` 구조체 안에 있는 **driver 구조체**는 드라이버와 관련된 정보를 담고 있습니다.
  - **name = "my_device_driver"**: 이 드라이버의 이름을 정의합니다. 커널 내에서 이 이름으로 드라이버를 구분하게 됩니다.
  - **of_match_table = my_driver_ids**: 이 드라이버가 **어떤 장치와 호환**되는지를 나타내는 **Device Tree**와의 매칭 정보입니다. `my_driver_ids` 배열에서 호환성을 정의합니다.

---

### 3. **Device Tree와 호환성 매칭 (of_device_id 구조체)**

```c
static struct of_device_id my_driver_ids[] = {
	{
		.compatible = "brightlight,mydev",
	}, { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, my_driver_ids);
```

- **of_device_id 구조체**는 **Device Tree**에서 이 드라이버가 어떤 장치와 **호환되는지**를 정의하는 테이블입니다.
  - `"compatible = "brightlight,mydev"`는 이 드라이버가 Device Tree에서 **"brightlight,mydev"**라는 호환성을 가진 장치에 연결됨을 의미합니다. 즉, Device Tree 파일에서 `"compatible = "brightlight,mydev"`로 정의된 장치가 발견되면 커널이 이 드라이버의 `probe()` 함수를 호출하게 됩니다.
  
- **MODULE_DEVICE_TABLE(of, my_driver_ids)**: 이 매크로는 커널 모듈이 지원하는 **Device Tree**의 호환성 정보를 정의하며, 해당 드라이버가 어떤 장치들과 연결될 수 있는지를 나타냅니다. 이를 통해 **u-boot**나 **커널 모듈 로더**가 모듈을 자동으로 적절한 장치에 매핑할 수 있게 합니다.

---

### 4. **Probe 함수: 장치와의 연결 및 초기화**

```c
static int dt_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	const char *label;
	int my_value, ret;

	printk("dt_probe - Now I am in the probe function!\n");

	/* Check for device properties */
	if(!device_property_present(dev, "label")) {
		printk("dt_probe - Error! Device property 'label' not found!\n");
		return -1;
	}
	if(!device_property_present(dev, "my_value")) {
		printk("dt_probe - Error! Device property 'my_value' not found!\n");
		return -1;
	}

	/* Read device properties */
	ret = device_property_read_string(dev, "label", &label);
	if(ret) {
		printk("dt_probe - Error! Could not read 'label'\n");
		return -1;
	}
	printk("dt_probe - label: %s\n", label);
	ret = device_property_read_u32(dev, "my_value", &my_value);
	if(ret) {
		printk("dt_probe - Error! Could not read 'my_value'\n");
		return -1;
	}
	printk("dt_probe - my_value: %d\n", my_value);

	return 0;
}
```

- **dt_probe()**는 이 플랫폼 드라이버에서 **가장 중요한 함수**로, 커널이 장치를 발견하고 이 드라이버를 연결할 때 호출됩니다.
  
- **pdev**는 `struct platform_device` 타입으로, 커널이 플랫폼 장치를 드라이버에 전달할 때 사용하는 구조체입니다. 여기서 장치와 관련된 정보를 사용하게 됩니다.

#### 주요 동작

1. **장치 속성 확인**:
   - `device_property_present()`를 사용하여 장치가 정의한 속성 `"label"`과 `"my_value"`가 **존재하는지 확인**합니다. 만약 이 속성이 Device Tree에서 정의되지 않았다면 에러 메시지를 출력하고 함수를 종료합니다.
   
2. **장치 속성 읽기**:
   - `device_property_read_string()`와 `device_property_read_u32()`를 사용하여 **Device Tree에 정의된 값들을 읽어옵니다**. `"label"`은 문자열 속성이며, `"my_value"`는 32비트 정수형 속성입니다. 만약 속성 읽기에 실패하면 에러 메시지를 출력하고 함수가 종료됩니다.
   
3. **장치 속성 출력**:
   - 읽어온 `"label"` 값과 `"my_value"` 값을 커널 로그에 출력합니다. 이는 디버깅을 돕기 위한 출력이며, 성공적으로 속성을 읽어왔음을 의미합니다.

---

### 5. **Remove 함수: 장치 제거 시 호출**

```c
static int dt_remove(struct platform_device *pdev) {
	printk("dt_probe - Now I am in the remove function\n");
	return 0;
}
```

- **dt_remove()**는 커널에서 장치가 **제거되거나 드라이버가 언로드**될 때 호출되는 함수입니다. 이 함수에서는 주로 장치와 관련된 자원 해제나 정리 작업을 수행합니다.
- 이 코드에서는 간단히 **로그 출력**만을 수행하며, 추가적인 자원 해제는 하지 않습니다.

---

### 6. **드라이버 등록 및 해제**

#### 1) **platform_driver_register()**

```c
static int __init my_init(void) {
	printk("dt_probe - Loading the driver...\n");
	if(platform_driver_register(&my_driver)) {
		printk("dt_probe - Error! Could not load driver\n");
		return -1;
	}
	return 0;
}
```

- `my_init()` 함수는 커널 모듈이 **로드될 때 호출**되는 함수입니다.
- `platform_driver_register()`는 이 드라이버를 커널에 **등록**하는 역할을 하며, 등록에 성공하면 커널은 장치 트리를 탐색하여 해당 장치와 **호환되는 장치**가 있을 경우 `probe()` 함수를 호출합니다.
- 만약 등록에 실패하면 에러 메시지를 출력하고, -1을 반환하여 모듈 로드를 실패로 처리합니다.

#### 2) **platform_driver_unregister()**

```c
static void __exit my_exit(void) {
	printk("dt_probe - Unload driver");
	platform_driver_unregister(&my_driver);
}
```

- `my_exit()` 함수는 모듈이 **언로드될 때 호출**됩니다.
- `platform_driver_unregister()`는 커널에서 **드라이버를 제거**하는 역할을 합니다. 이 과정에서 드라이버는 더 이상 장치와 연결되지 않으며, 시스템에서 완전히 해제됩니다.

---



## B. Demo
![dt_probe](https://github.com/user-attachments/assets/7c04872f-83d5-4622-845b-1bc227e85e29)
![dt_probe2](https://github.com/user-attachments/assets/846eaa94-59ef-464e-8041-9d8ea239f9ef)
![dt_probe3](https://github.com/user-attachments/assets/4c6de300-00e4-46a2-a61b-5082dd37db3f)



## C. 코드 구현 방법
이 코드는 플랫폼 드라이버가 로드될 때 장치 트리(Device Tree)에서 특정 장치 및 해당 속성을 파싱하여 처리하는 Linux 커널 모듈입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`my_init` 호출)
   - `module_init()` 매크로에 의해 **my_init** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **platform_driver_register()** 호출
   - **플랫폼 드라이버 등록**: `platform_driver_register()` 함수로 `my_driver` 구조체에 정의된 플랫폼 드라이버를 커널에 등록합니다.
   - 드라이버가 등록되면 커널은 장치 트리에 정의된 장치와 해당 드라이버의 호환성을 확인하고, 호환되는 장치가 있는 경우 `dt_probe()` 함수를 호출하여 장치를 처리합니다.
   - 등록에 실패하면 에러 메시지를 출력하고 함수가 종료됩니다.

### 2. 드라이버가 등록된 장치 트리와 매칭될 때 (`dt_probe` 호출)
   - 플랫폼 장치가 드라이버와 매칭되면 **dt_probe** 함수가 호출됩니다.

#### 2-1. **device_property_present()** 호출 (속성 확인)
   - **속성 존재 여부 확인**: `device_property_present()` 함수를 사용해 장치 트리에서 `label`과 `my_value` 속성이 있는지 확인합니다.
   - 속성이 없으면 에러 메시지를 출력하고 `-1`을 반환하여 프로브 과정을 중지합니다.

#### 2-2. **device_property_read_string()** 및 **device_property_read_u32()** 호출 (속성 읽기)
   - **속성 읽기**: `device_property_read_string()`으로 `label` 속성을 읽고, `device_property_read_u32()`로 `my_value` 속성을 읽습니다.
   - 읽기에 실패하면 에러 메시지를 출력하고 함수가 종료됩니다.
   - 성공적으로 속성을 읽으면 해당 값을 출력합니다.

### 3. 모듈 언로드 시 (`my_exit` 호출)
   - `module_exit()` 매크로에 의해 **my_exit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **platform_driver_unregister()** 호출
   - **플랫폼 드라이버 등록 해제**: `platform_driver_unregister()` 함수로 등록된 플랫폼 드라이버를 시스템에서 해제합니다.
   - 이로 인해 더 이상 해당 장치에 대한 처리를 수행하지 않게 됩니다.

### 함수 호출 순서 요약

1. **my_init()** → 모듈 로드, 플랫폼 드라이버 등록
   - `platform_driver_register()`로 플랫폼 드라이버 등록

2. **dt_probe()** → 장치가 드라이버와 매칭될 때 호출
   - `device_property_present()`로 장치 트리 속성 확인
   - `device_property_read_string()` 및 `device_property_read_u32()`로 속성 읽기

3. **my_exit()** → 모듈 언로드, 플랫폼 드라이버 해제
   - `platform_driver_unregister()`로 플랫폼 드라이버 해제

이 순서는 플랫폼 드라이버가 장치 트리에서 정의된 특정 장치와 매칭될 때 해당 속성을 파싱하여 처리하는 과정을 설명합니다.
