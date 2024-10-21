
# Linux Kernel Module: Kthread Example
## 관련개념
`kthread()`와 `kernel_thread()`는 리눅스 커널에서 커널 스레드를 생성하는 데 사용되는 함수들입니다. 이 함수들은 각각 특정 시점에서 커널 스레드 생성과 관리에 사용되었으며, 현대 리눅스 커널에서는 주로 `kthread` 관련 함수를 사용하여 커널 스레드를 관리합니다. 두 함수의 개념과 차이점, 그리고 사용 이유를 설명하겠습니다.

### 1. **kthread() 및 관련 함수들**

`kthread`는 커널 스레드를 생성하고 관리하는 데 사용되는 커널 API입니다. 커널 스레드는 사용자 공간이 아닌 커널 공간에서 실행되며, 커널 내에서 주기적인 작업이나 특정 작업을 비동기적으로 처리할 수 있도록 해줍니다. 리눅스 커널 2.6 이후로 `kthread` API가 도입되었으며, 현재 커널 스레드를 생성하는 데 권장되는 방법입니다.(한컴아카데미 최신커널(6.x)교육)

#### `kthread`의 장점:
- 커널 스레드를 안전하게 생성하고 종료할 수 있는 고수준 API를 제공합니다.
- 스레드의 시작과 종료를 명시적으로 제어할 수 있습니다.
- 다양한 스레드 관련 함수들을 활용해 스레드 동작을 세밀하게 관리할 수 있습니다.
해당 코드에서 `kthread`(커널 스레드)를 사용하는 방법을 단계별로 설명하겠습니다.

### 1. **커널 스레드 정의**
먼저, 두 개의 전역 변수로 커널 스레드를 정의합니다:
```c
static struct task_struct *kthread_1;
static struct task_struct *kthread_2;
```
- `struct task_struct`는 커널 스레드를 관리하는 구조체입니다. 커널에서 각 스레드는 `task_struct`로 관리됩니다.
- 이 변수들은 각각 `kthread_1`과 `kthread_2`라는 커널 스레드를 가리킵니다.

### 2. **커널 스레드 함수 정의**
다음으로, 커널 스레드가 실행할 함수인 `thread_function()`이 정의되어 있습니다:
```c
int thread_function(void *thread_nr) {
    unsigned int i = 0;
    int t_nr = *(int *) thread_nr;

    /* 작업 루프 */
    while(!kthread_should_stop()){
        printk("kthread - Thread %d is executed! Counter val: %d\n", t_nr, i++);
        msleep(t_nr * 1000); // 스레드마다 다른 주기로 실행
    }

    printk("kthread - Thread %d finished execution!\n", t_nr);
    return 0;
}
```
- `thread_function()`은 스레드가 반복적으로 실행할 작업을 정의하는 함수입니다.
- 매개변수로 스레드 번호(`thread_nr`)를 전달받아, 각 스레드가 자신만의 실행 간격을 가지도록 설정합니다.
- `kthread_should_stop()`는 스레드가 중지 명령을 받았는지 여부를 확인하는 함수로, 이 함수가 `true`를 반환하면 스레드는 종료됩니다.
- 스레드는 `msleep(t_nr * 1000)`을 통해 각 스레드마다 다른 시간 동안 대기합니다:
  - `t_nr = 1`인 스레드는 1초(1000ms)마다 실행됩니다.
  - `t_nr = 2`인 스레드는 2초(2000ms)마다 실행됩니다.

### 3. **모듈 초기화 및 스레드 생성 (ModuleInit)**
모듈이 로드될 때 실행되는 `ModuleInit()` 함수에서 커널 스레드를 생성하고 실행시킵니다:

```c
static int __init ModuleInit(void) {
    printk("kthread - Init threads\n");

    kthread_1 = kthread_create(thread_function, &t1, "kthread_1");
    if(kthread_1 != NULL){
        /* 스레드를 시작합니다 */
        wake_up_process(kthread_1);
        printk("kthread - Thread 1 was created and is running now!\n");
    } else {
        printk("kthread - Thread 1 could not be created!\n");
        return -1;
    }

    kthread_2 = kthread_run(thread_function, &t2, "kthread_2");
    if(kthread_2 != NULL)
        printk("kthread - Thread 2 was created and is running now!\n");
    else {
        printk("kthread - Thread 2 could not be created!\n");
        kthread_stop(kthread_1);
        return -1;
    }

    printk("kthread - Both threads are running now!\n");

    return 0;
}
```

#### 주요 단계:
- **`kthread_create()`**: `kthread_1` 스레드를 생성합니다.
  - `thread_function`은 스레드가 실행할 함수입니다.
  - `&t1`은 스레드 번호로, `t1 = 1`로 설정되었습니다.
  - `"kthread_1"`은 스레드의 이름입니다.
  - 스레드를 생성한 후 `wake_up_process()`를 호출해 스레드를 실행시킵니다.
  - 만약 스레드 생성이 실패하면(`NULL` 반환) 오류 메시지를 출력하고 모듈 초기화가 실패하게 됩니다.

- **`kthread_run()`**: `kthread_2` 스레드를 생성하고 바로 실행합니다.
  - 이 함수는 `kthread_create()`와 `wake_up_process()`를 결합한 함수로, 생성과 동시에 실행됩니다.
  - `thread_function`은 스레드가 실행할 함수이고, `&t2`는 스레드 번호 `t2 = 2`를 전달합니다.
  - `"kthread_2"`는 스레드의 이름입니다.
  - 만약 스레드 생성이 실패하면, `kthread_1` 스레드를 중지하고 초기화를 실패합니다.

### 4. **모듈 종료 및 스레드 중지 (ModuleExit)**
모듈이 언로드될 때 실행되는 `ModuleExit()` 함수에서는 두 스레드를 중지합니다:

```c
static void __exit ModuleExit(void) {
    printk("kthread - Stop both threads\n");
    kthread_stop(kthread_1);
    kthread_stop(kthread_2);
}
```

- **`kthread_stop()`**: 이 함수는 지정된 커널 스레드를 중지시킵니다. 이 함수는 스레드가 `kthread_should_stop()`에서 중지 요청을 확인한 후 스레드를 종료시키고, `thread_function()`이 종료되도록 합니다.
- `kthread_stop()`을 호출하면 스레드가 깨워져서 즉시 중지 루틴을 수행하고 종료됩니다.

### 요약:
1. **스레드 생성**:
   - `kthread_create()`를 사용해 `kthread_1`을 생성하고, `wake_up_process()`로 스레드를 실행합니다.
   - `kthread_run()`을 사용해 `kthread_2`를 생성하고, 생성과 동시에 실행합니다.

2. **스레드 실행**:
   - 스레드의 작업 함수인 `thread_function()`은 스레드가 주기적으로 실행할 동작을 정의합니다.
   - `kthread_should_stop()`을 통해 스레드가 종료
  
---
### 2. **kernel_thread()**(구버전)
`kernel_thread()`는 리눅스 커널에서 커널 스레드를 생성하는 함수로, `kthread()` 함수가 도입되기 전에는 커널 스레드를 생성하는 기본 방법이었습니다. 이 함수는 현재는 구식 방식으로, 대부분의 최신 리눅스 커널에서는 더 이상 사용되지 않으며 `kthread` API가 그 역할을 대체하고 있습니다.

### 3. **`kthread()`와 `kernel_thread()`의 차이점**

| **특징**                   | **kthread()**                                      | **kernel_thread()**                             |
|----------------------------|---------------------------------------------------|-------------------------------------------------|
| **사용 여부**              | 현재 사용되는 커널 스레드 생성 방식               | 오래된 방식, 현재는 잘 사용되지 않음            |
| **사용법**                 | 고수준 API로 간편하게 커널 스레드를 생성하고 관리 | 더 낮은 수준의 API로, 추가적인 제어 필요        |
| **스레드 종료**            | `kthread_stop()` 및 `kthread_should_stop()` 제공   | 수동으로 스레드 종료 처리가 필요함             |
| **추가 기능**              | 스레드 이름 지정, 스레드 시작/종료 제어 등 기능 제공 | 기본적인 스레드 생성만 가능                     |
| **도입 시기**              | 리눅스 커널 2.6 이후                               | 구식 API, 리눅스 커널 2.6 이전 사용             |


## 설명
간단한 실습을 통해 커널 스레드(kthread)의 사용법을 보여줍니다. 이 모듈은 두 개의 커널 스레드를 생성하여 각각의 카운터를 증가시키고, 해당 활동을 커널 로그에 기록합니다.
이 실습은 리눅스 커널 모듈 내에서 커널 스레드를 생성하고 관리하는 방법을 설명합니다.

- kthread 1은 1초마다 실행됩니다.
- kthread 2는 2초마다 실행됩니다.

## 커널 로그 출력

다음은 모듈을 로드한 후 kthread의 동작을 관찰한 커널 로그의 샘플 출력입니다:

![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/a8af8cb0-1f3a-4512-9faa-0b6a81d9b496)


