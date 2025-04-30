
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>   // wait() ফাংশনের জন্য
#include <sys/shm.h>    // shared memory এর জন্য

int global_var = 10;    // গ্লোবাল ভেরিয়েবল

int main()
{
    int local_var = 20, status;
    int *local_address, *global_address;
    pid_t pid;
    key_t key;
    int shmid;
    int shared_var = 30;

    local_address = &local_var;
    global_address = &global_var;

    // ফর্ক করার আগের অবস্থা
    printf("Before fork():\n");
    printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
    printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

    // শেয়ার্ড মেমোরি তৈরি করা
    key = 1234;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget: ");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory ID: %d\n", shmid);

    // চাইল্ড প্রসেস তৈরি করা
    pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // চাইল্ড প্রসেস
        printf("\n[Child Process]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // চাইল্ড প্রসেসে ভেরিয়েবল পরিবর্তন
        local_var = 100;
        global_var = 200;

        printf("\n[Child Process After Modification]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // শেয়ার্ড মেমোরিতে কানেক্ট করা
        void *shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (void *)-1)
        {
            perror("shmat: ");
            exit(EXIT_FAILURE);
        }

        // শেয়ার্ড মেমোরিতে মান লেখা
        int *shm_ptr = (int *)shmaddr;
        *shm_ptr = 20;

        // চাইল্ড প্রসেসের লুপ
        for (int i = 0; i < 10; i++)
        {
            printf("Child Process Loop: %d\n", i);
            sleep(1);
        }

        // শেয়ার্ড মেমোরি থেকে পড়া
        printf("Child process writing to shared memory: %d\n", shm_ptr[0]);

        // শেয়ার্ড মেমোরি থেকে ডিটাচ করা
        if (shmdt(shmaddr) == -1)
        {
            perror("shmdt: ");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS); // চাইল্ড প্রসেস শেষ
    }
    else
    {
        // প্যারেন্ট প্রসেস
        printf("\n[Parent Process]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // প্যারেন্ট প্রসেসে ভেরিয়েবল পরিবর্তন
        local_var = 100;
        global_var = 200;

        printf("\n[Parent Process After Modification]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // চাইল্ড প্রসেস শেষ হওয়ার জন্য অপেক্ষা
        wait(&status);

        // প্যারেন্ট প্রসেস শেয়ার্ড মেমোরিতে কানেক্ট করে
        void *shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (void *)-1)
        {
            perror("shmat: ");
            exit(EXIT_FAILURE);
        }

        // প্যারেন্ট প্রসেসের লুপ
        for (int i = 0; i < 10; i++)
        {
            printf("hi, I am parent process\n");
            sleep(1);
        }

        // শেয়ার্ড মেমোরি থেকে পড়া
        int *shm_ptr = (int *)shmaddr;
        printf("Parent process reading from shared memory: %d\n", shm_ptr[0]);

        // শেয়ার্ড মেমোরি থেকে ডিটাচ করা
        if (shmdt(shmaddr) == -1)
        {
            perror("shmdt: ");
            exit(EXIT_FAILURE);
        }

        // প্যারেন্ট প্রসেস আবার নিজের কাজ চালিয়ে যাবে
        for (int i = 0; i < 10; i++)
        {
            printf("\n[Parent Process Loop]\n");
            printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
            printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);
            sleep(1);
        }

        printf("\nSuccessfully terminated.\n");
    }

    return 0;
}
```

---

### ✅ কী কী উন্নতি করলাম:
- বারবার `printf` গুলোকে সুন্দরভাবে আলাদা করেছি যেন পড়তে সহজ হয়।
- কমেন্টগুলো বাংলায় লিখেছি যাতে সহজে বোঝা যায়।
- অপ্রয়োজনীয় কমেন্ট সরিয়ে পরিস্কার করেছি।
- কোডের ইন্ডেন্টেশন ঠিক করে দিয়েছি।

---


ভাই! ❤️  
আমি প্রথমে সংক্ষেপে বলছি তোমার কোডের **মূল কাজ** কী, তারপর একটু বিস্তারিতভাবে **ধাপে ধাপে** ব্যাখ্যা করবো যেন পুরোটা পরিষ্কার হয়।

---
### ➔ সংক্ষেপে তোমার কোডের আসল কাজ:

✅ `fork()` দিয়ে **একটি নতুন চাইল্ড প্রসেস** তৈরি করা হয়।  
✅ চাইল্ড এবং প্যারেন্ট দুইজনেই **নিজের আলাদা কপি** নিয়ে কাজ করে।  
✅ **শেয়ার্ড মেমোরি** ব্যবহার করে, চাইল্ড একটি ডেটা লিখে এবং প্যারেন্ট সেই ডেটা পড়ে।  
✅ চাইল্ড প্রসেস শেষ হওয়ার পর, প্যারেন্ট প্রসেস শেয়ার্ড মেমোরি থেকে ডেটা পড়ে।  
✅ পাশাপাশি, **local variable** আর **global variable** এর এড্রেস এবং ভ্যালু কেমন পরিবর্তন হয়, সেটাও দেখা হয়।

---

### ➔ ধাপে ধাপে পুরো ব্যাখ্যা:

---

### **১. শুরুতেই ভেরিয়েবল ডিক্লেয়ার করা হয়**
- `global_var = 10;` — একটা **গ্লোবাল ভেরিয়েবল**।
- `local_var = 20;` — একটা **লোকাল ভেরিয়েবল** (main function এর ভেতরে)।
- `shared_var = 30;` — শেয়ার্ড মেমোরি তে কাজের জন্য।

---

### **২. fork() এর আগে প্রিন্ট করা হয়**
- আগে দেখানো হয়:
  - global variable এর ভ্যালু এবং address
  - local variable এর ভ্যালু এবং address

---

### **৩. শেয়ার্ড মেমোরি তৈরি করা হয় (shmget দিয়ে)**
- `shmget(key, sizeof(int), IPC_CREAT | 0666);`
- এখানে একটা **key (1234)** ব্যবহার করা হয়েছে।
- একটা **integer size** এর জন্য শেয়ার্ড মেমোরি allocate করা হয়।
- একটা **shmid (shared memory id)** পাওয়া যায়।

---

### **৪. fork() করা হয়**
- `fork()` দিয়ে **চাইল্ড** প্রসেস তৈরি হয়।
- এখন দুইটা প্রসেস চলছে: প্যারেন্ট ও চাইল্ড।  
  কিন্তু দুজনের নিজেদের আলাদা **লোকাল কপি** আছে ভেরিয়েবল এর।

---

### **৫. যদি Child Process হয়:**
- প্রথমে চাইল্ড নিজের ভেরিয়েবল প্রিন্ট করে।
- তারপর:
  - `local_var = 100;`
  - `global_var = 200;` — চাইল্ড নিজের কপিতে পরিবর্তন করে।
- **শেয়ার্ড মেমোরিতে** (`shmat`) অ্যাটাচ হয়।
- শেয়ার্ড মেমোরিতে `20` লিখে দেয়।
- তারপর কিছু লুপ চালিয়ে বারবার প্রিন্ট করে।
- শেষে শেয়ার্ড মেমোরি থেকে **detach (shmdt)** হয়ে যায়।

---

### **৬. যদি Parent Process হয়:**
- প্রথমে প্যারেন্ট নিজের ভেরিয়েবল প্রিন্ট করে।
- তারপর:
  - `local_var = 100;`
  - `global_var = 200;` — প্যারেন্ট নিজের কপিতে পরিবর্তন করে।
- প্যারেন্ট `wait(&status);` দিয়ে চাইল্ড প্রসেস শেষ হওয়া পর্যন্ত অপেক্ষা করে।
- চাইল্ড শেষ হওয়ার পর, প্যারেন্টও **শেয়ার্ড মেমোরিতে** অ্যাটাচ হয়।
- কিছুক্ষণ লুপ চালায় (hi i am parent process)।
- এরপর শেয়ার্ড মেমোরি থেকে ডেটা পড়ে (child লিখে দিয়েছিল `20`)।
- শেষে শেয়ার্ড মেমোরি থেকে **detach (shmdt)** হয়।
- আর কিছু লুপ চালিয়ে গ্লোবাল ও লোকাল ভেরিয়েবল দেখায়।

---

### **৭. কোডের মূল শিক্ষা (Key Concepts):**
- **fork()** এ দুইটা প্রসেস তৈরি হয় যারা আলাদা কপি নিয়ে কাজ করে।
- গ্লোবাল আর লোকাল ভেরিয়েবল কপি হয়ে যায় (শেয়ার করে না)।
- **শেয়ার্ড মেমোরি** ব্যবহার করলে দুইটা আলাদা প্রসেস ডেটা শেয়ার করতে পারে।
- চাইল্ড লিখে, প্যারেন্ট পড়ে নেয় — **ইন্টার প্রসেস কমিউনিকেশন (IPC)** এর একটা রিয়েল লাইফ এক্সাম্পল।
- **shmat()**, **shmdt()**, **shmget()** এগুলা ব্যবহার করে মেমোরি ম্যানেজ করা হয়।

---

### ➔ সহজ কথায়
এই কোড শেখাচ্ছে কিভাবে:
- fork() দিয়ে প্রসেস তৈরি করতে হয়,
- ভিন্ন প্রসেসের মেমোরি আলাদা হয়,
- আবার চাইলে শেয়ার্ড মেমোরির মাধ্যমে দুই প্রসেসের মাঝে ডেটা আদান-প্রদান করা যায়।

---


