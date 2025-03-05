

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, burstTime, waitingTime;
};

// Comparator function to sort processes by burst time (SJF)
bool compare(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input burst time for each process
    cout << "Enter Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "P" << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    // Sorting processes by burst time (SJF)
    sort(processes.begin(), processes.end(), compare);

    int totalWaitingTime = 0, sum = 0;
    
    // Calculating waiting time
    processes[0].waitingTime = 0; // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        sum += processes[i - 1].burstTime;
        processes[i].waitingTime = sum;
        totalWaitingTime += processes[i].waitingTime;
    }

    // Displaying process waiting times
    cout << "\nProcess | Burst Time | Waiting Time\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "   P" << processes[i].id << "    |     " 
             << processes[i].burstTime << " ms   |     " 
             << processes[i].waitingTime << " ms\n";
    }

    // Calculating and displaying average waiting time
    double avgWaitingTime = (double)totalWaitingTime / n;
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avgWaitingTime << " ms\n";

    return 0;
}
```

---

### **Example Output**
```
Enter number of processes: 4
Enter Burst Time for each process:
P1: 6
P2: 8
P3: 7
P4: 3

Process | Burst Time | Waiting Time
-----------------------------------
   P4    |     3 ms   |     0 ms
   P1    |     6 ms   |     3 ms
   P3    |     7 ms   |     9 ms
   P2    |     8 ms   |     16 ms

Average Waiting Time: 7.00 ms
```

---

### **Key Features:**
✅ Uses `#include<bits/stdc++.h>` for simplicity  
✅ Uses **struct** to store process data  
✅ **Sorts processes** by burst time (SJF)  
✅ **Calculates waiting time** for each process  
✅ **Displays formatted output**  
✅ **Computes average waiting time**  

Let me know if you need modifications! 🚀
