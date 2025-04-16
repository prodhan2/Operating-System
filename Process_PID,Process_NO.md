#define GNU_GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sched.h>

int main()
{
    pid_t child_status;
    int process_no;

    child_status = fork();

    if (child_status == 0)
    {
        // Child process
        process_no = sched_getcpu();
        printf("Child Process:\n");
        printf("   Child PID  = %d\n", getpid());
        printf("   Parent PID = %d\n", getppid());
        printf("   Running on CPU Core = %d\n", process_no);
    }
    else if (child_status > 0)
    {
        // Parent process
        process_no = sched_getcpu();
        printf("Parent Process:\n");
        printf("   Parent PID = %d\n", getpid());
        printf("   Child PID  = %d\n", child_status);
        printf("   Running on CPU Core = %d\n", process_no);
    }
    else
    {
        // Fork failed
        perror("Fork failed");
    }

    return 0;
}



এই প্রোগ্রামটি C প্রোগ্রামিং ভাষায় লেখা, যা একটি প্রক্রিয়া (process) সৃষ্টি করে এবং এটি প্রদর্শন করে যে, প্যারেন্ট এবং চাইল্ড প্রক্রিয়া কোন CPU কোরে রান করছে। এখানে কোডের প্রতিটি অংশ ব্যাখ্যা করা হল বাংলায়:

1. **`#define GNU_GNU_SOURCE`**  
   এটি একটি ম্যাক্রো ডিফাইনেশন, যা GNU সিস্টেমের ফিচারগুলো সক্রিয় করতে ব্যবহৃত হয়। এটি কিছু বিশেষ ফাংশন এবং এক্সটেনশন ব্যবহার করতে সাহায্য করে, যা সাধারণত অন্যান্য সিস্টেমে পাওয়া যায় না।

2. **`#include <unistd.h>`**  
   `unistd.h` লাইব্রেরি ফাইলটি বিভিন্ন সিস্টেম কলের জন্য প্রয়োজনীয় হেডার ফাইল, যেমন `fork()` এবং `getpid()`।

3. **`#include <stdio.h>`**  
   `stdio.h` লাইব্রেরি ফাইলটি ইনপুট ও আউটপুট (I/O) কার্যক্রমের জন্য ব্যবহার হয়, যেমন `printf()` ফাংশন।

4. **`#include <sys/types.h>`**  
   এই লাইব্রেরিটি ডেটা টাইপগুলো সংজ্ঞায়িত করে, যেমন `pid_t` (প্রক্রিয়ার আইডি)।

5. **`#include <sched.h>`**  
   এই হেডারটি সিডিউলিং সম্পর্কিত ফাংশনগুলোর জন্য প্রয়োজনীয়, যেমন `sched_getcpu()` যা কোন CPU কোরে প্রক্রিয়া চলছে তা জানায়।

### কোডের মূল অংশ:

1. **`pid_t child_status;`**  
   এখানে `child_status` নামে একটি পরিবর্তনশীল ডিক্লেয়ার করা হয়েছে যা চাইল্ড প্রক্রিয়ার PID (Process ID) ধারণ করবে।

2. **`int process_no;`**  
   `process_no` নামক একটি পরিবর্তনশীল যা সিস্টেমে প্রক্রিয়া যে CPU কোরে চলছে, সেটি ধারণ করবে।

3. **`child_status = fork();`**  
   `fork()` সিস্টেম কলটি নতুন একটি চাইল্ড প্রক্রিয়া তৈরি করে। এটি দুটি ভ্যালু রিটার্ন করে:
   - চাইল্ড প্রক্রিয়ার ক্ষেত্রে ০ রিটার্ন হয়।
   - প্যারেন্ট প্রক্রিয়ার ক্ষেত্রে চাইল্ড প্রক্রিয়ার PID রিটার্ন হয়।

4. **`if (child_status == 0)`**  
   যদি `child_status` ০ হয়, তাহলে এটি চাইল্ড প্রক্রিয়া, যেখানে `sched_getcpu()` ফাংশনটি চাইল্ড প্রক্রিয়া যে CPU কোরে চলছে তা ফেরত দেয়।

   **চাইল্ড প্রক্রিয়ার তথ্য:**  
   - `getpid()` দ্বারা চাইল্ড প্রক্রিয়ার PID (প্রক্রিয়ার আইডি) পাওয়া যায়।
   - `getppid()` দ্বারা প্যারেন্ট প্রক্রিয়ার PID পাওয়া যায়।
   - `sched_getcpu()` দ্বারা CPU কোরের সংখ্যা পাওয়া যায় যেখানে চাইল্ড প্রক্রিয়া চলছে।

5. **`else if (child_status > 0)`**  
   যদি `child_status` পজিটিভ হয়, অর্থাৎ এটি প্যারেন্ট প্রক্রিয়া, তখন এটি চাইল্ড প্রক্রিয়ার PID এবং যে CPU কোরে প্যারেন্ট প্রক্রিয়া চলছে তা দেখাবে।

6. **`else`**  
   যদি `fork()` ফাংশনটি কোনো কারণে সফল না হয়, তাহলে এটি `fork failed` ত্রুটি দেখাবে।

### আউটপুট:
- চাইল্ড প্রক্রিয়া ও প্যারেন্ট প্রক্রিয়ার PID, প্যারেন্ট PID, এবং CPU কোরের তথ্য আউটপুট হবে।
- উদাহরণ:  
  ```
  Parent Process:
     Parent PID = 1234
     Child PID  = 1235
     Running on CPU Core = 0

  Child Process:
     Child PID  = 1235
     Parent PID = 1234
     Running on CPU Core = 1
  ```

এই কোডটি মূলত প্যারেন্ট এবং চাইল্ড প্রক্রিয়ার সিস্টেমে কোন CPU কোরে চলছে, সেটি দেখানোর জন্য লেখা হয়েছে।
