### **`fork()` কেন ব্যবহার করা হয়?**  

Linux-এ `fork()` একটি গুরুত্বপূর্ণ সিস্টেম কল, যা একটি নতুন **child process** তৈরি করতে ব্যবহৃত হয়। এটি **parent process** কে দুটি আলাদা process এ বিভক্ত করে:  

1. **Parent Process** (মূল প্রক্রিয়া)  
2. **Child Process** (নতুন তৈরি হওয়া প্রক্রিয়া)

---

### **🔹 `fork()` কেন ব্যবহৃত হয়?**  

#### **1️⃣ মাল্টিপ্রসেসিং (Parallel Execution)**
`fork()` ব্যবহারের মাধ্যমে একাধিক কাজ একই সাথে চালানো যায়।  
✅ **উদাহরণ**: সার্ভার-প্রোগ্রাম যেখানে প্রতিটি নতুন ক্লায়েন্টের জন্য একটি নতুন process তৈরি করা হয়।

#### **2️⃣ Process Duplication (প্রক্রিয়া অনুলিপি করা)**
Parent process-এর কপি তৈরি করা হয়, যেখানে একই কোড চলে, কিন্তু আলাদা Process ID (PID) থাকে।  
✅ **উদাহরণ**: Shell বা Terminal-এ যখন নতুন কমান্ড চালানো হয়, তখন একটি নতুন process তৈরি হয়।

#### **3️⃣ Parent এবং Child একসাথে কাজ করতে পারে**
একটি প্রোগ্রাম `fork()` ব্যবহার করে **একই সময়ে** দুইটি কাজ করতে পারে।  
✅ **উদাহরণ**: একদিকে ফাইল পড়ছে, অন্যদিকে প্রোগ্রাম নতুন প্রক্রিয়ার মাধ্যমে কিছু গণনা করছে।

#### **4️⃣ Server-Client Communication (সার্ভার ক্লায়েন্ট মডেল)**
একটি সার্ভার `fork()` ব্যবহার করে প্রতিটি ক্লায়েন্টের জন্য আলাদা child process তৈরি করতে পারে।  
✅ **উদাহরণ**: Apache HTTP Server প্রতিটি অনুরোধের জন্য আলাদা process তৈরি করে।

#### **5️⃣ Process Isolation (আলাদা প্রসেস তৈরি)**
Child এবং Parent আলাদাভাবে চলতে পারে, যা **মাল্টিটাস্কিং এবং প্রোগ্রাম ক্র্যাশ প্রতিরোধ** করতে সাহায্য করে।  
✅ **উদাহরণ**: কোনো প্রোগ্রাম যদি child process-এ চলতে গিয়ে ক্র্যাশ করে, parent process চালু থাকে।

---

### **🔹 `fork()` কীভাবে কাজ করে?**
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // নতুন প্রসেস তৈরি
    
    if (pid < 0) {
        printf("Fork failed!\n");
    } 
    else if (pid == 0) {
        printf("This is the Child process! PID: %d, PPID: %d\n", getpid(), getppid());
    } 
    else {
        printf("This is the Parent process! PID: %d, Child PID: %d\n", getpid(), pid);
    }
    
    return 0;
}
```

---

### **🔹 `fork()` ব্যবহার করার পর কী ঘটে?**
1. `fork()` কল করার পর **একই কোড Parent এবং Child উভয়ের জন্য চলবে**।
2. `fork()` একটি নতুন process তৈরি করলে **Child process-এর PID (Process ID) আলাদা হয়**।
3. `fork()` **parent process-এ child-এর PID রিটার্ন করে**, আর **child process-এ `0` রিটার্ন করে**।

---

### **🔹 কম্পাইল ও রান করার পদ্ধতি**
```sh
gcc fork_example.c -o fork_example
./fork_example
```

### **🔹 সম্ভাব্য আউটপুট**
```
This is the Parent process! PID: 1234, Child PID: 1235
This is the Child process! PID: 1235, PPID: 1234
```
☑ Parent-এর PID: `1234`  
☑ Child-এর PID: `1235`  
☑ Child-এর Parent PID (`PPID`): `1234`  

---

### **সারসংক্ষেপ**
✅ `fork()` ব্যবহারের মাধ্যমে মাল্টিপ্রসেসিং সহজ হয়।  
✅ Parent এবং Child process সমান্তরালভাবে কাজ করতে পারে।  
✅ `fork()` মূলত সার্ভার, মাল্টিটাস্কিং এবং মাল্টিপ্রসেস অ্যাপ্লিকেশন তৈরিতে ব্যবহৃত হয়।  

💡 **`fork()` সংক্রান্ত কোনো প্রশ্ন থাকলে জানাতে পারেন! 🚀**
