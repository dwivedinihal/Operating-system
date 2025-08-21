#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int start;
    int finish;
    bool completed;
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Reset processes
void processReset(vector<Process> &p, vector<int> &arrival, vector<int> &burst, int n) {
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].arrival = arrival[i];
        p[i].burst = burst[i];
        p[i].start = -1;
        p[i].finish = -1;
        p[i].completed = false;
    }
}

// Print Gantt Chart
void printProcess(vector<int> &gantt) {
    int last = -1;
    cout << "Gantt Chart : ";
    for (int x : gantt) {
        if (x != last) {
            cout << "P" << x << " ";
            last = x;
        }
    }
    cout << "\n";
}

// Shortest Job First Scheduling (Non-Preemptive)
void SJFS(vector<Process> &p, int n) {
    int ttime = 0, completed = 0;
    vector<int> gantt;

    while (completed < n) {
        int idx = -1, mini_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= ttime && p[i].burst < mini_burst) {
                mini_burst = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            ttime++; // idle
            continue;
        }

        p[idx].start = ttime;
        ttime += p[idx].burst;
        p[idx].finish = ttime;
        p[idx].completed = true;

        // Calculate TAT and WT
        p[idx].tat = p[idx].finish - p[idx].arrival;
        p[idx].wt = p[idx].tat - p[idx].burst;

        completed++;

        for (int t = p[idx].start; t < p[idx].finish; t++) {
            gantt.push_back(p[idx].pid);
        }
    }

    printProcess(gantt);

    // Print process table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst
             << "\t" << p[i].finish << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << (totalWT / n) << "\n";
    cout << "Average Turnaround Time: " << (totalTAT / n) << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> arrival(n), burst(n);
    cout << "Enter Arrival times: ";
    for (int i = 0; i < n; i++) cin >> arrival[i];
    cout << "Enter Burst times: ";
    for (int i = 0; i < n; i++) cin >> burst[i];

    vector<Process> p(n);
    cout << "\n--------- SJF Non-Preemptive ---------\n";
    processReset(p, arrival, burst, n);
    SJFS(p, n);

    return 0;
}
