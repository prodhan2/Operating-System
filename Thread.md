---

```markdown
# 🎯 C++ এ মাল্টিথ্রেডিং ও CPU কোর শনাক্তকরণ

এই প্রোগ্রামটি `pthreads` ব্যবহার করে দুটি থ্রেড তৈরি করে — একটি অ্যাডিশন (যোগ) এবং একটি সাবস্ট্রাকশন (বিয়োগ) এর জন্য। প্রতিটি থ্রেড কোন CPU কোরে চলছে তা `sched_getcpu()` ফাংশনের মাধ্যমে নির্ধারণ করা হয়।

> ⚙️ কম্পাইল ও রান করার নির্দেশনা:
> ```bash
> g++ -D_GNU_SOURCE t.cpp -o t -pthread
> ./t
> ```

## 🔍 সোর্স কোড

```cpp
// GNU extension সক্রিয় করার জন্য
#define _GNU_SOURCE

#include <unistd.h>     // POSIX API
#include <pthread.h>    // pthread ব্যবহার করার জন্য
#include <stdio.h>      // printf ফাংশনের জন্য
#include <sched.h>      // sched_getcpu() ফাংশনের জন্য

// বিয়োগ থ্রেডের ফাংশন
void* subtraction(void* arg)
{
    int process_no = sched_getcpu(); // থ্রেড কোন CPU কোরে চলছে তা বের করা
    printf("Subtraction thread running on CPU core: %d\n", process_no);
    return NULL;
}

// যোগ থ্রেডের ফাংশন
void* addition(void* arg)
{
    int process_no = sched_getcpu(); // থ্রেড কোন CPU কোরে চলছে তা বের করা
    printf("Addition thread running on CPU core: %d\n", process_no);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2; // দুইটি থ্রেড ডিক্লেয়ার করা

    // দুটি থ্রেড তৈরি করা
    pthread_create(&thread1, NULL, addition, NULL);      // যোগের জন্য
    pthread_create(&thread2, NULL, subtraction, NULL);   // বিয়োগের জন্য

    // থ্রেডগুলোর কাজ শেষ হওয়া পর্যন্ত অপেক্ষা করা
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
```

## 🖥️ সম্ভাব্য আউটপুট

```text
Addition thread running on CPU core: 2
Subtraction thread running on CPU core: 3
```
