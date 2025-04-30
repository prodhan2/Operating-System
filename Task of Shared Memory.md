

- **Shared Memory কী?**  
- **Task বা কাজ কীভাবে চলে?**  
- **Real example/diagram সহ** ব্যাখ্যা?  

আমি খুব সুন্দর করে তোমাকে ব্যাখ্যা দিচ্ছি — 🔥

---

# 🔵 Shared Memory (ভাগ করা মেমোরি) কী?

- **Shared memory** হলো এমন একটি মেমোরি ব্লক, যেখানে **একাধিক প্রসেস একসাথে Access করতে পারে**।
- এটা **fastest form of inter-process communication (IPC)** (মানে দুইটা প্রসেসের মধ্যে ডেটা আদান-প্রদান করার সবচেয়ে দ্রুততম উপায়)।
- একবার যদি দুইটা প্রসেস একই shared memory তে যুক্ত হয়, তারা **directly** তথ্য **share/read/write** করতে পারে।

---

# 🔵 মূল কাজের ধাপ (Task of Shared Memory):

আমি একটা ফ্লো বানালাম 👇

```plaintext
প্রসেস ১ এবং প্রসেস ২
      |
      V
1. একটি Shared Memory Create করা হয় (shmget দিয়ে)
      |
2. প্রসেসগুলো সেই Shared Memory তে Attach হয় (shmat দিয়ে)
      |
3. একটি প্রসেস ডেটা Write করে
      |
4. অন্য প্রসেস সেই ডেটা Read করে
      |
5. কাজ শেষ হলে Detach করা হয় (shmdt দিয়ে)
      |
6. অবশেষে, Shared Memory Destroy করা হয় (shmctl দিয়ে, যদি প্রয়োজন হয়)
```

---

# 🔵 আরও পরিষ্কার ভাবে বুঝি: একটি বাস্তব উদাহরণ

ধরো, তুমি একটা রেস্টুরেন্ট চালাও।  
- **Parent** = Manager
- **Child** = Worker

**Shared Memory = একটা হোয়াইট বোর্ড, যেটাতে সবাই ইনফরমেশন লিখতে পারে, পড়তেও পারে।**

✅ Manager (Parent) বলে দিলো বোর্ডে: "**Order Ready: Burger**"  
✅ Worker (Child) দেখে ফেলে: "**Burger pick kore customer ke dey**"  

এখানে "বোর্ড" ই হচ্ছে **Shared Memory** —  
একবার লেখা হলে, সবাই সেটা Access করতে পারছে।

---

# 🔵 তোমার প্রোগ্রামে কী হচ্ছে?

| ধাপ | Parent | Child |
|:---|:---|:---|
| 1 | একটি Shared Memory বানায় | |
| 2 | fork() করে Child তৈরি করে | |
| 3 | | Shared Memory তে 20 লিখে |
| 4 | | Memory Detach করে |
| 5 | Parent দেখছে Shared Memory এর ডেটা (20) |
| 6 | Parent Memory detach করে |
| 7 | Parent চাইল্ডের কাজ শেষ হওয়া পর্যন্ত wait করে |
| 8 | Success message দেয় |

---

# 🔵 ছোট্ট একটা Figure 📈

```
[ Parent Process ]
    |
    | fork()
    V
[ Child Process ]
    |
    |--- shmat --> [ Shared Memory (int value) ] <-- shmat ---|
    |                                                        |
    |--- Write: 20                                            |
    |                                                        |
    |                --- Read: 20 ---                        |
    |
(Detach, Wait, Done)
```

---

# 🔥 Summary এক লাইনে:

> Shared memory হলো — একাধিক প্রসেসের মধ্যে দ্রুততম ডেটা শেয়ারিং করার একটা পদ্ধতি, যেখানে আলাদা message passing ছাড়াই ডেটা Access করা যায়।

---

# ➡️ যদি চাও, আমি তোমাকে:
- একটি **আরও বড় Practical Example**
- অথবা **Diagram সহ একটা Full Life Cycle (Create → Attach → Use → Detach → Destroy)**
- অথবা **Quiz/MCQ Practice** বানিয়ে দিতে পারি! 🎯  

বলবে? ❤️  
(তাহলে তুমি ১০০% Shared Memory expert হয়ে যাবে ভাই!) ✅  
Ready? 🚀
চমৎকার! 😍  
তুমি বললে — তাই আমি তোমার জন্য **Diagram + Full Life Cycle + Practical Example + ছোট্ট MCQ Practice** বানাচ্ছি।  
চলো শুরু করি — 🚀

---

# 🛑 Shared Memory Life Cycle (Diagram + Step by Step)

```plaintext
1. Create
     |
     V
  shmget()  <-- একটা নতুন shared memory বানাও
     |
2. Attach
     |
     V
  shmat()   <-- এই shared memory কে প্রসেসে যুক্ত করো
     |
3. Use
     |
     V
  Read / Write <-- এখানে data পড়বে বা লিখবে
     |
4. Detach
     |
     V
  shmdt()   <-- কাজ শেষ? তাহলে মেমোরি থেকে Disconnect করো
     |
5. Destroy (optional)
     |
     V
  shmctl( IPC_RMID ) <-- পুরো shared memory delete করো
```

---

# 🔵 Full Practical Example (C++ Style) 🔥

```cpp
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    // Step 1: Create Shared Memory
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);

    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }
    cout << "Shared Memory Created: ID = " << shmid << endl;

    // Step 2: Fork a child
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child Process
        int* shared_data = (int*)shmat(shmid, nullptr, 0);
        *shared_data = 200; // Step 3: Write
        cout << "Child Wrote: " << *shared_data << endl;
        shmdt(shared_data); // Step 4: Detach
    }
    else {
        // Parent Process
        wait(nullptr); // Wait for child
        int* shared_data = (int*)shmat(shmid, nullptr, 0);
        cout << "Parent Read: " << *shared_data << endl;
        shmdt(shared_data); // Detach

        // Step 5: Destroy Shared Memory
        shmctl(shmid, IPC_RMID, nullptr);
        cout << "Shared Memory Destroyed." << endl;
    }
    return 0;
}
```

---
✅ এখানে:
- **Child লিখছে:** 200
- **Parent পড়ছে:** 200
- **শেষে মেমোরি মুছে ফেলছে।**

---

# 🔥 ছোট্ট MCQ Practice (Practice Questions)  

**Question 1:**  
🔹 কোন ফাংশন দিয়ে Shared Memory তৈরি করা হয়?  
**a)** fork()  
**b)** shmget()  
**c)** exec()  
**d)** shmdt()  

➡️ **Answer:** b) shmget()

---

**Question 2:**  
🔹 কোন ফাংশন দিয়ে Shared Memory মেমোরি থেকে ছাড়ানো হয় (detach)?  
**a)** shmctl()  
**b)** shmdt()  
**c)** shmat()  
**d)** malloc()  

➡️ **Answer:** b) shmdt()

---

**Question 3:**  
🔹 Child যদি shared memory তে কিছু লিখে, Parent সেটা পড়ে নিতে পারে কি?  
**a)** হ্যাঁ  
**b)** না  

➡️ **Answer:** a) হ্যাঁ

---

# 🔵 Summary 🚀

| স্টেপ | কাজ |
|:-----|:----|
| shmget() | Shared Memory তৈরি করা |
| shmat() | Shared Memory যুক্ত করা |
| *read/write* | Data ব্যবহার করা |
| shmdt() | মেমোরি থেকে ছাড়ানো |
| shmctl() | মেমোরি মুছে ফেলা |

---

# 🎯 Ready to be a Shared Memory Champion!  


