
---

### ✅ কোড (বাংলা কমেন্টসহ):
```c
//Inter Process Communication using Unnamed Pipe
//nazmulhasan77
#include <unistd.h>     // POSIX সিস্টেম কলগুলোর জন্য যেমন fork(), pipe(), sleep()।
#include <stdlib.h>     // মেমোরি এলোকেশন, প্রসেস কন্ট্রোল, কনভার্সন ইত্যাদি ফাংশনের জন্য
#include <stdio.h>      // ইনপুট-আউটপুট ফাংশনের জন্য
#include <sys/wait.h>   // wait() ফাংশনের জন্য, যাতে প্যারেন্ট চাইল্ডকে অপেক্ষা করতে পারে
#include <sched.h>      // sched_getcpu() ব্যবহার করার জন্য
#include <string.h>     // স্ট্রিং সংক্রান্ত কাজের জন্য

int main(){
    pid_t pid;
    int processor_no;
    int pipe_fd[2]; // pipe_fd[0] -> read, pipe_fd[1] -> write
    char buffer[80]; // মেসেজ রাখার জন্য

    // পাইপ তৈরি করার আগে পাইপ ফাইল ডিসক্রিপ্টর দেখানো
    printf("Pipe Descriptor: %d ,%d\n", pipe_fd[0], pipe_fd[1]);

    // পাইপ তৈরি
    pipe(pipe_fd);

    // পাইপ তৈরি হওয়ার পর ডিসক্রিপ্টর দেখানো
    printf("Pipe Descriptor: %d ,%d\n", pipe_fd[0], pipe_fd[1]); // সাধারণত: 3(read), 4(write)

    // প্রসেস তৈরি
    pid = fork();
    if(pid < 0){
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        // চাইল্ড প্রসেস
        pid = getpid();
        processor_no = sched_getcpu(); // কোন প্রসেসরে চলছে তা বের করা
        printf("Child PID: %d, Processor No: %d\n", pid, processor_no);

        const char *msg = "Type a messege to parent: ";
        write(1, msg, strlen(msg)); // ইউজারকে মেসেজ টাইপ করতে বলা
        read(0, buffer, sizeof(buffer)); // ইউজারের কাছ থেকে মেসেজ ইনপুট নেয়া

        close(pipe_fd[0]); // রিড এন্ড বন্ধ
        write(pipe_fd[1], buffer, strlen(buffer)); // মেসেজ লিখে দেয়া পাইপে
        close(pipe_fd[1]); // রাইট এন্ড বন্ধ
    } else {
        // প্যারেন্ট প্রসেস
        pid = getpid();
        processor_no = sched_getcpu();
        printf("Parent PID: %d, Processor No: %d\n", pid, processor_no);

        close(pipe_fd[1]); // রাইট এন্ড বন্ধ
        read(pipe_fd[0], buffer, sizeof(buffer)); // পাইপ থেকে বার্তা পড়া
        close(pipe_fd[0]); // রিড এন্ড বন্ধ

        write(1, buffer, strlen(buffer)); // মনিটরে বার্তা দেখানো

        int status;
        wait(&status); // চাইল্ড প্রসেস শেষ হওয়া পর্যন্ত অপেক্ষা
    }

    exit(EXIT_SUCCESS);
}
```

---

### ✅ Sample Output:

যদি ইউজার ইনপুট দেয়: `Hello from child process\n`  
তাহলে আউটপুট হবে এমন:

```
Pipe Descriptor: 32767 ,0
Pipe Descriptor: 3 ,4
Parent PID: 5156, Processor No: 1
Child PID: 5157, Processor No: 1
Type a messege to parent: Hello from child process
Hello from child process
```

---

### 📌 ব্যাখ্যা:
1. প্রথমে unnamed pipe তৈরি হয়, যার read-end (`pipe_fd[0]`) এবং write-end (`pipe_fd[1]`) থাকে।
2. `fork()` এর মাধ্যমে চাইল্ড প্রসেস তৈরি হয়।
3. চাইল্ড প্রসেস ইউজারের কাছ থেকে মেসেজ নেয় এবং পাইপের write-end-এ লিখে দেয়।
4. প্যারেন্ট প্রসেস সেই মেসেজ read-end থেকে পড়ে মনিটরে প্রিন্ট করে।

---
