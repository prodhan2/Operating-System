In Linux, a process has multiple types of IDs, including:  

1. **Process ID (PID)** – Unique identifier for a process.  
2. **Parent Process ID (PPID)** – ID of the parent process.  
3. **Real User ID (RUID)** – The user ID of the process owner.  
4. **Effective User ID (EUID)** – Determines the privileges of the process.  
5. **Group IDs (RGID, EGID)** – Real and effective group IDs of the process.  
6. **Session ID (SID)** – Identifier of the session leader.  
7. **Process Group ID (PGID)** – Identifies a group of related processes.  

### **C Program to Print All Process IDs**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Process ID (PID): %d\n", getpid());
    printf("Parent Process ID (PPID): %d\n", getppid());
    printf("Process Group ID (PGID): %d\n", getpgid(0));
    printf("Session ID (SID): %d\n", getsid(0));
    printf("Real User ID (RUID): %d\n", getuid());
    printf("Effective User ID (EUID): %d\n", geteuid());
    printf("Real Group ID (RGID): %d\n", getgid());
    printf("Effective Group ID (EGID): %d\n", getegid());

    return 0;
}
```

### **Explanation**
- `getpid()` → Gets the current process ID.  
- `getppid()` → Gets the parent process ID.  
- `getpgid(0)` → Gets the process group ID of the calling process.  
- `getsid(0)` → Gets the session ID of the calling process.  
- `getuid()` → Gets the real user ID.  
- `geteuid()` → Gets the effective user ID.  
- `getgid()` → Gets the real group ID.  
- `getegid()` → Gets the effective group ID.  

### **Compile & Run**
```sh
gcc process_info.c -o process_info
./process_info
```

### **Sample Output**
```
Process ID (PID): 12345
Parent Process ID (PPID): 54321
Process Group ID (PGID): 12345
Session ID (SID): 1000
Real User ID (RUID): 1000
Effective User ID (EUID): 1000
Real Group ID (RGID): 1000
Effective Group ID (EGID): 1000
```

Let me know if you need further modifications! 🚀
