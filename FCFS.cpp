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

    int sum = 0, totalWaitingTime = 0;

    // Calculating total waiting time
    for (int i = 0; i < n; i++) {
        totalWaitingTime += sum;
        sum += burstTime[i];
    }

    // Calculating and displaying average waiting time
    double avgWaitingTime = (double)totalWaitingTime / n;
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << avgWaitingTime << " ms" << endl;

    return 0;
}
