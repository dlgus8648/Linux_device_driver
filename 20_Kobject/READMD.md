# 20_Kobject



--

### 1. **Sysfs**

리눅스 커널에서 **장치, 드라이버, 버스, 클래스** 등의 하드웨어 정보를 사용자 공간에 **노출**하고, 이를 **구성**할 수 있는 방법이 필요했습니다. 기존에는 `/proc` 파일 시스템을 사용하여 이러한 정보를 제공했지만, **/proc 파일 시스템**은 주로 **프로세스 관련 정보**를 관리하는 데 사용되었기 때문에, 점차 복잡해졌고 **비효율적인 사용**이 문제로 떠올랐습니다.

**Sysfs**는 이러한 문제를 해결하기 위해 도입되었습니다.
Sysfs는 `/sys` 디렉토리를 통해 **커널 객체(Kernel Objects)**의 구조와 관련된 정보를 **계층적 파일 시스템** 형태로 사용자에게 노출합니다. 
이 파일 시스템은 **Kobject**와 **Device Model**을 기반으로 하며, **장치 및 드라이버, 버스, 클래스, 기타 커널 객체들**에 대한 정보를 효율적으로 관리할 수 있도록 합니다.

- **계층적 구조**: 커널 객체는 파일 시스템의 디렉토리 구조처럼 **계층적**으로 구성됩니다. 각 객체는 하위 객체를 가질 수 있고, 객체의 속성은 **파일**로 표시됩니다.
- **사용자 접근 가능**: `/sys` 파일 시스템을 통해 **장치 상태**를 사용자 공간에서 확인하고, 필요한 경우 이를 수정할 수 있습니다.
- **표준화된 접근 방법**: 각 객체는 파일이나 디렉토리로 표현되며, 표준적인 방식으로 **읽기/쓰기**가 가능하여 장치나 커널 구성 요소를 손쉽게 관리할 수 있습니다.
- **하드웨어 정보 접근성 향상**: 사용자 공간에서 하드웨어 장치와 드라이버 정보를 확인하고, 관리할 수 있는 표준 인터페이스를 제공합니다.
- **구조적 관리**: **Kobject**를 기반으로 커널 객체들이 **계층적**으로 관리되며, 이는 커널 내부 구조를 보다 체계적으로 관리할 수 있게 해줍니다.
- **유연성 증가**: 커널에서 장치나 버스, 클래스 등의 다양한 객체에 대한 정보를 유연하게 관리하고 **확장**할 수 있게 되었습니다.

---

### 2. **참조 카운트 (Reference Counting)**

리눅스 커널은 다양한 **객체(메모리 블록, 파일, 장치 등)**를 동적으로 생성하고, 여러 **참조**가 발생할 수 있는 환경입니다. 이러한 객체들은 여러 프로세스나 스레드에서 참조될 수 있으며, 참조가 끝나면 **메모리 해제**가 필요합니다. 하지만 이 과정에서 **누가 객체를 언제 해제할지**를 결정하는 것은 어렵습니다. **불필요하게 남아 있는 객체**는 메모리 누수를 초래하고, 반대로 **해제된 객체에 접근**하려고 하면 **시스템 오류**를 일으킬 수 있습니다.

**참조 카운트(Reference Counting)** 는 이러한 문제를 해결하기 위해 도입되었습니다. 참조 카운트는 객체에 **얼마나 많은 프로세스나 스레드가 참조**하고 있는지를 **카운팅**하고, 참조가 더 이상 없을 때 해당 객체를 안전하게 **해제**하는 방법입니다.

- **참조 증가**: 객체가 참조될 때마다 참조 카운트를 증가시킵니다.
- **참조 감소**: 객체의 참조가 끝나면 참조 카운트를 감소시킵니다.
- **자동 메모리 관리**: 참조 카운트가 **0이 되면** 객체를 메모리에서 해제합니다.

---

### 3. **Kset**

리눅스 커널은 다양한 **커널 객체(Kobject)**를 다룹니다. 이들은 **계층적**으로 구성되어 있어, 객체 간의 **관계**를 설정하고 **그룹화**하는 기능이 필요합니다. 하지만 각 객체를 **개별적으로 관리**하는 것은 복잡하고, 여러 객체가 함께 관리되어야 할 때 **일관성 유지**와 **동기화**가 어려울 수 있습니다.

**Kset**은 이러한 문제를 해결하기 위해 도입되었습니다. **Kset**은 여러 개의 **Kobject**를 **그룹화**하여 관리할 수 있는 구조로, **공통된 속성**이나 **목적**을 가진 객체들을 한데 묶어 관리할 수 있게 합니다. Kset을 통해 **Kobject**의 집합을 만들고, 이 집합을 기반으로 여러 객체를 보다 체계적으로 관리할 수 있습니다.

- **객체 그룹화**: 공통된 목적을 가진 **Kobject**들을 그룹으로 묶어 **일관성 있게 관리**할 수 있습니다.
- **계층적 구조**: Kset은 Kobject의 **계층적 관계**를 표현할 수 있습니다. 즉, 하나의 Kset이 또 다른 Kset을 포함할 수 있습니다.
- **동기화 및 관리**: Kset을 통해 **동일한 그룹 내의 객체들**을 관리하고, 그들과 관련된 **이벤트**나 **참조 카운트** 등을 쉽게 동기화할 수 있습니다.

- **구조적 관리**: Kobject를 **그룹화**하여 커널 내에서 구조적으로 객체들을 관리할 수 있습니다.
- **효율적인 동기화**: 여러 객체들이 그룹 내에서 동작할 때, **일관된 동작**과 **동기화**가 가능해집니다.
- **유연한 계층 구조**: Kobject와 Kset의 **계층적 구조**를 통해 객체들이 보다 유연하게 관리되고, 재사용성이 증가합니다.

---

## B. Demo
![kobject4](https://github.com/user-attachments/assets/34957dea-86d1-483b-ad1b-f2e39d693d3f)
![kobject3](https://github.com/user-attachments/assets/3ccad4dc-9abf-4551-a2d4-cc78a0870488)
![kobject2](https://github.com/user-attachments/assets/434094a9-13bf-44f9-8d56-3a0f840555b6)
![kobject1](https://github.com/user-attachments/assets/c3157693-2bc4-4113-b074-27f6e3d3b15f)

## C. 코드 구현방법
이 코드는 Linux 커널 모듈에서 kobject를 생성하고, sysfs 파일 시스템에 이를 노출시켜 사용자 공간에서 값을 읽고 쓸 수 있도록 하는 예제입니다. `foo`, `baz`, `bar`라는 세 개의 변수를 kobject의 속성으로 만들고, sysfs를 통해 이 변수들에 접근하는 방식입니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`example_init` 호출)
   - `module_init()` 매크로에 의해 **example_init** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **kobject_create_and_add()** 호출
   - **kobject 생성 및 등록**: `kobject_create_and_add()` 함수로 `/sys/kernel/` 디렉터리에 `kobject_example`이라는 이름의 kobject를 생성하고 등록합니다.
   - kobject가 생성되지 않으면 메모리 부족으로 인해 에러 메시지를 출력하고 함수가 종료됩니다.

#### 1-2. **sysfs_create_group()** 호출
   - **sysfs 속성 그룹 생성**: `sysfs_create_group()` 함수로 `foo`, `baz`, `bar` 속성 그룹을 kobject에 등록합니다. 
   - 이 함수는 kobject에 속한 여러 속성을 한 번에 생성하는 역할을 하며, 성공적으로 생성되면 `/sys/kernel/kobject_example/` 디렉터리 아래에 `foo`, `baz`, `bar` 속성이 파일로 나타납니다.
   - 그룹 생성에 실패하면 kobject를 해제하고 함수가 종료됩니다.

### 2. 사용자 공간에서 sysfs 파일 조작 시 (`foo_show`, `foo_store`, `b_show`, `b_store` 호출)
   - **읽기와 쓰기**: 사용자 애플리케이션이 sysfs 파일(`/sys/kernel/kobject_example/foo`, `/sys/kernel/kobject_example/baz`, `/sys/kernel/kobject_example/bar`)을 읽거나 쓸 때, 다음 함수들이 호출됩니다.

#### 2-1. **foo_show()** 호출
   - **`foo` 속성 읽기**: `cat /sys/kernel/kobject_example/foo`와 같은 명령을 실행하면 `foo_show()` 함수가 호출되어 `foo` 변수를 출력합니다.

#### 2-2. **foo_store()** 호출
   - **`foo` 속성 쓰기**: `echo 10 > /sys/kernel/kobject_example/foo`와 같은 명령을 실행하면 `foo_store()` 함수가 호출되어 사용자로부터 전달받은 값을 `foo` 변수에 저장합니다.

#### 2-3. **b_show()** 호출
   - **`baz` 또는 `bar` 속성 읽기**: `cat /sys/kernel/kobject_example/baz` 또는 `cat /sys/kernel/kobject_example/bar` 명령을 실행하면 `b_show()` 함수가 호출되어 각각의 변수를 출력합니다.

#### 2-4. **b_store()** 호출
   - **`baz` 또는 `bar` 속성 쓰기**: `echo 20 > /sys/kernel/kobject_example/baz` 또는 `echo 30 > /sys/kernel/kobject_example/bar` 명령을 실행하면 `b_store()` 함수가 호출되어 사용자로부터 전달받은 값을 `baz` 또는 `bar` 변수에 저장합니다.

### 3. 모듈 언로드 시 (`example_exit` 호출)
   - `module_exit()` 매크로에 의해 **example_exit** 함수가 모듈이 언로드될 때 호출됩니다.

#### 3-1. **kobject_put()** 호출
   - **kobject 해제**: `kobject_put()` 함수로 kobject를 해제합니다. 이는 생성된 kobject 및 관련된 sysfs 파일들을 제거합니다.

### 함수 호출 순서 요약

1. **example_init()** → 모듈 로드, kobject 생성 및 sysfs 파일 생성
   - `kobject_create_and_add()`로 `/sys/kernel/kobject_example/`에 kobject 생성
   - `sysfs_create_group()`으로 `foo`, `baz`, `bar` 속성 생성

2. **foo_show()**, **foo_store()**, **b_show()**, **b_store()** → sysfs 파일을 통한 읽기/쓰기
   - `foo_show()` → `cat /sys/kernel/kobject_example/foo` 호출 시
   - `foo_store()` → `echo 10 > /sys/kernel/kobject_example/foo` 호출 시
   - `b_show()` → `cat /sys/kernel/kobject_example/baz` 또는 `cat /sys/kernel/kobject_example/bar` 호출 시
   - `b_store()` → `echo 20 > /sys/kernel/kobject_example/baz` 또는 `echo 30 > /sys/kernel/kobject_example/bar` 호출 시

3. **example_exit()** → 모듈 언로드, kobject 및 sysfs 파일 해제
   - `kobject_put()`로 kobject 해제 및 sysfs 파일 제거

이 순서는 kobject를 생성하고, sysfs를 통해 사용자 공간에서 kobject의 속성에 접근하는 전체 과정을 보여줍니다.
