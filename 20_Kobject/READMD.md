
## B. 함수 호출 순서
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
