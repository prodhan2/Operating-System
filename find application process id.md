### **🔍 Find Firefox Process ID (PID) Using C in Linux**
Here are different ways to find the **Process ID (PID)** of **Firefox** in C.

---

## ✅ **Method 1: Using `system()` with `pgrep` (Easiest)**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Finding Firefox PID...\n");
    system("pgrep firefox"); // Calls 'pgrep firefox' and prints PID
    return 0;
}
```
🔹 **Compilation & Execution:**
```sh
gcc find_firefox_pid.c -o find_firefox_pid
./find_firefox_pid
```
🔹 **Example Output:**
```
Finding Firefox PID...
5643
```
---

## ✅ **Method 2: Using `popen()` to Capture PID**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char pid[10];

    fp = popen("pgrep firefox", "r"); // Run 'pgrep firefox' and get output
    if (fp == NULL) {
        printf("Failed to find process\n");
        return 1;
    }

    if (fgets(pid, sizeof(pid), fp) != NULL) {
        printf("Firefox Process ID: %s", pid);
    } else {
        printf("Firefox is not running.\n");
    }

    pclose(fp);
    return 0;
}
```
🔹 **Example Output:**
```
Firefox Process ID: 5643
```
---

## ✅ **Method 3: Manually Scan `/proc` (Advanced)**
This method checks each process in `/proc/` and finds **Firefox's PID** manually.

```c
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dp;
    struct dirent *entry;
    FILE *fp;
    char path[40], line[100], process_name[50] = "firefox";

    dp = opendir("/proc");
    if (dp == NULL) {
        perror("Cannot open /proc");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_DIR && strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
            snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);
            fp = fopen(path, "r");

            if (fp) {
                fgets(line, sizeof(line), fp); // First line is process name
                fclose(fp);

                if (strstr(line, process_name)) {
                    printf("Firefox PID: %s\n", entry->d_name);
                }
            }
        }
    }

    closedir(dp);
    return 0;
}
```
🔹 **Example Output:**
```
Firefox PID: 5643
```
---

## **📌 Summary**
| Method | Description | Complexity |
|--------|------------|------------|
| `system("pgrep firefox")` | Fastest way using shell command | ⭐ Easy |
| `popen("pgrep firefox", "r")` | Captures PID output for further use | ⭐⭐ Moderate |
| Scan `/proc` manually | Finds process without external commands | ⭐⭐⭐ Advanced |

For **quick results**, use **Method 1 or 2**.  
For **custom solutions**, use **Method 3**.

Let me know if you need modifications! 🚀
