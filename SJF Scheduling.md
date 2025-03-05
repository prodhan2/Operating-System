

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;

    cout << "How many processes? ";
    cin >> n;

    int burstTime[n];
    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++) {
        cin >> burstTime[i];
    }

    // Sorting burst times in ascending order (SJF)
    sort(burstTime, burstTime + n);

    int sum = 0, totalWaitingTime = 0;

    // Calculating total waiting time
    for (int i = 0; i < n; i++) {
        cout << "Waiting time for P" << i + 1 << ": " << sum << " ms" << endl;
        totalWaitingTime += sum;
        sum += burstTime[i];
    }

    // Calculating average waiting time
    double avgWaitingTime = (double)totalWaitingTime / n;
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << avgWaitingTime << " ms" << endl;

    return 0;
}
```

### **Explanation of Changes**:
1. **Sort Syntax Fix**: You missed the correct syntax for the `sort()` function. It should be:
   ```cpp
   sort(burstTime, burstTime + n);
   ```
   This sorts the array of burst times in ascending order (since we are using Shortest Job First (SJF) Scheduling).

2. **Waiting Time Output**: When printing the waiting time, I adjusted the loop to print `P` followed by the process number. The loop now correctly prints for each process in sequence, starting from `P1` (1-indexed).

### **Example Output**:

```
How many processes? 4
Enter burst times: 6 8 7 3
Waiting time for P1: 0 ms
Waiting time for P2: 3 ms
Waiting time for P3: 9 ms
Waiting time for P4: 16 ms
Average Waiting Time: 7.00 ms
```

### **What’s happening in the program**:
- First, we read the number of processes and burst times.
- Then, we sort the burst times in ascending order for SJF.
- We calculate the waiting time for each process by keeping a running sum of the burst times.
- Finally, we calculate and print the average waiting time.

