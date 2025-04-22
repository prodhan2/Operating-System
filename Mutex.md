
- দুটি থ্রেড (`addition` ও `subtraction`) আছে
- `main` থ্রেডও কাজ করছে
- `pthread_mutex` ব্যবহার করে **thread-safe** ভাবে `x` পরিবর্তন করা হচ্ছে
- প্রতিটি অংশ সুন্দরভাবে কমেন্ট করা হয়েছে যাতে তুমি এক নজরে বুঝতে পারো কী হচ্ছে

---

### ✅ Final Single Mutex Thread Example (With Bengali Comments)

```cpp
#define GNU_GNU_SOURCE
#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>

using namespace std;

// 🔧 শেয়ার করা ভ্যারিয়েবল
int x = 0;

// 🔒 Mutex object ডিক্লেয়ার
pthread_mutex_t key;

// ➕ Addition Thread Function
void* addition(void* arg) {
    for (int i = 0; i < 10; i++) {
        int cpu = sched_getcpu(); // কোন CPU তে চলছে

        pthread_mutex_lock(&key);  // 🔐 Lock নিচ্ছে
        x++;                       // x বাড়াচ্ছে
        printf("Addition thread on CPU %d => x = %d\n", cpu, x);
        pthread_mutex_unlock(&key); // 🔓 Lock ছাড়ছে

        usleep(100000); // কিছুটা দেরি (0.1 sec)
    }
    return NULL;
}

// ➖ Subtraction Thread Function
void* subtraction(void* arg) {
    for (int i = 0; i < 10; i++) {
        int cpu = sched_getcpu(); // কোন CPU তে চলছে

        pthread_mutex_lock(&key);  // 🔐 Lock নিচ্ছে
        x--;                       // x কমাচ্ছে
        printf("Subtraction thread on CPU %d => x = %d\n", cpu, x);
        pthread_mutex_unlock(&key); // 🔓 Lock ছাড়ছে

        usleep(120000); // কিছুটা দেরি (0.12 sec)
    }
    return NULL;
}

// 🧠 Main Thread
int main() {
    pthread_t tid1, tid2;

    pthread_mutex_init(&key, NULL); // 🔧 Mutex initialize

    pthread_create(&tid1, NULL, addition, NULL);     // ➕ addition thread শুরু
    pthread_create(&tid2, NULL, subtraction, NULL);  // ➖ subtraction thread শুরু

    // 🧵 Main thread loop
    for (int i = 0; i < 10; i++) {
        int cpu = sched_getcpu();

        pthread_mutex_lock(&key); // 🔐 x পড়তে lock নিচ্ছে
        printf("Main thread on CPU %d => x = %d\n", cpu, x);
        pthread_mutex_unlock(&key); // 🔓 ছাড়ছে

        usleep(110000); // একটু দেরি (0.11 sec)
    }

    pthread_join(tid1, NULL); // ➕ থ্রেড শেষ না হওয়া পর্যন্ত অপেক্ষা
    pthread_join(tid2, NULL); // ➖ থ্রেড শেষ না হওয়া পর্যন্ত অপেক্ষা

    pthread_mutex_destroy(&key); // 🧹 mutex destroy

    return 0;
}
```

---

### 🧠 Output Example (উদাহরণ):
```
Addition thread on CPU 0 => x = 1
Main thread on CPU 0 => x = 1
Subtraction thread on CPU 1 => x = 0
Addition thread on CPU 0 => x = 1
Subtraction thread on CPU 1 => x = 0
Main thread on CPU 0 => x = 0
...
```
