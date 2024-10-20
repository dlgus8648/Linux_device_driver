
## B. 함수 호출 순서
두 개의 커널 스레드를 생성하고, 스레드 간에 공유 자원에 접근할 때 상호 배제를 위해 뮤텍스(mutex)를 사용하는 Linux 커널 모듈입니다. 각 스레드는 지정된 지연 시간 후에 임계 구역(critical section)에 접근하여 자원을 안전하게 처리합니다. 함수 호출 순서는 다음과 같습니다.

### 1. 모듈 로드 시 (`ModuleInit` 호출)
   - `module_init()` 매크로에 의해 **ModuleInit** 함수가 커널 모듈이 로드될 때 호출됩니다.

#### 1-1. **mutex_init()** 호출
   - **뮤텍스 초기화**: `mutex_init()` 함수는 글로벌 변수 `lock`에 뮤텍스를 초기화합니다. 이후 이 뮤텍스는 스레드 간의 자원 접근을 동기화하는 데 사용됩니다.

#### 1-2. **kthread_create()** 호출 (첫 번째 스레드 생성)
   - **첫 번째 커널 스레드 생성**: `kthread_create()` 함수로 `thread_function`을 실행하는 첫 번째 스레드(`kthread_1`)를 생성합니다.
   - 성공적으로 스레드가 생성되면 `wake_up_process()` 함수로 스레드를 시작합니다.
   - 실패 시 "Thread 1 could not be created!" 메시지를 출력하고 함수가 종료됩니다.

#### 1-3. **kthread_run()** 호출 (두 번째 스레드 생성 및 실행)
   - **두 번째 커널 스레드 생성 및 실행**: `kthread_run()` 함수는 `thread_function`을 실행하는 두 번째 스레드(`kthread_2`)를 생성하고 바로 실행합니다.
   - 성공 시 "Thread 2 was created and is running now!" 메시지를 출력합니다.
   - 실패 시 "Thread 2 could not be created!" 메시지를 출력하고, 첫 번째 스레드(`kthread_1`)를 중지한 후 함수가 종료됩니다.

#### 1-4. **모든 스레드가 정상적으로 실행 중** 
   - 두 스레드가 성공적으로 생성되면 "Both threads are running now!" 메시지를 출력합니다.

### 2. 스레드 실행 중 (`thread_function` 호출)
   - 각 스레드는 **thread_function** 함수에 의해 실행됩니다.

#### 2-1. **뮤텍스 잠금** (`mutex_lock()`)
   - 각 스레드는 "Thread X is executed!" 메시지를 출력한 후 **mutex_lock()**을 호출하여 뮤텍스를 잠급니다. 
   - 다른 스레드가 이미 임계 구역에 있다면, 해당 스레드는 뮤텍스가 해제될 때까지 대기합니다.

#### 2-2. **임계 구역 접근**
   - 스레드가 뮤텍스 잠금에 성공하면 "Thread X is in critical section!" 메시지를 출력하고 임계 구역에 들어갑니다.
   - 각 스레드는 `msleep()`으로 지정된 시간만큼 대기합니다. 스레드 1은 1초, 스레드 2는 500ms 동안 대기합니다.

#### 2-3. **뮤텍스 해제** (`mutex_unlock()`)
   - 대기 시간이 끝나면 "Thread X is leaving the critical section!" 메시지를 출력하고 **mutex_unlock()**을 호출하여 뮤텍스를 해제합니다.
   - 다른 스레드가 임계 구역에 접근할 수 있도록 뮤텍스가 해제됩니다.

#### 2-4. **스레드 종료**
   - 임계 구역을 떠난 후 "Thread X finished execution!" 메시지를 출력하고 스레드가 종료됩니다.

### 3. 모듈 언로드 시 (`ModuleExit` 호출)
   - `module_exit()` 매크로에 의해 **ModuleExit** 함수가 모듈이 언로드될 때 호출됩니다.
   - 현재 코드에서는 스레드 종료나 리소스 해제와 관련된 작업을 수행하지 않지만, 스레드가 중지되었다는 메시지를 출력합니다.

### 함수 호출 순서 요약

1. **ModuleInit()** → 모듈 로드, 뮤텍스 및 스레드 생성
   - `mutex_init()`으로 뮤텍스 초기화
   - `kthread_create()`로 첫 번째 스레드 생성 및 시작
   - `kthread_run()`으로 두 번째 스레드 생성 및 시작

2. **thread_function()** → 스레드 실행 중
   - `mutex_lock()`으로 뮤텍스 잠금
   - 임계 구역에 접근, `msleep()`으로 대기
   - `mutex_unlock()`으로 뮤텍스 해제
   - 스레드 종료

3. **ModuleExit()** → 모듈 언로드
   - 스레드 중지 메시지 출력 (현재는 스레드를 중지하는 코드는 포함되어 있지 않음)

이 순서는 커널 모듈에서 두 개의 커널 스레드를 생성하고, 뮤텍스를 사용하여 스레드 간의 임계 구역 접근을 제어하는 방법을 설명합니다.
