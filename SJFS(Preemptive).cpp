#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    int rt;
    int tat;
    int wt;
    int remain;
};

int main() {
    int n;
    cout << "Enter Number of Processes : ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter arrival time of P" << i + 1 << " : ";
        cin >> p[i].at;
        cout << "Enter burst time of P" << i + 1 << "   : ";
        cin >> p[i].bt;
        p[i].remain = p[i].bt;
    }

    int completed = 0;
    int currtime = 0;
    double total_tat = 0;
    double total_wt = 0;
    double total_rt = 0;
    vector<int> gantt;
    vector<bool> started(n, false);

    while (completed < n) {
        int idx = -1;
        int min_remain = INT_MAX;

        // find process with smallest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currtime && p[i].remain > 0) {
                if (p[i].remain < min_remain) {
                    min_remain = p[i].remain;
                    idx = i;
                } else if (p[i].remain == min_remain) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        // CPU idle
        if (idx == -1) {
            gantt.push_back(-1);
            currtime++;
            continue;
        }

        // first time execution
        if (!started[idx]) {
            p[idx].st = currtime;
            p[idx].rt = p[idx].st - p[idx].at;
            started[idx] = true;
        }

        // gantt.push_back(p[idx].pid);
        p[idx].remain--;
        currtime++;

        // process completed
        if (p[idx].remain == 0) {
            p[idx].ct = currtime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat += p[idx].tat;
            total_rt += p[idx].rt;
            total_wt += p[idx].wt;

            completed++;   
        }
    }

    cout << "\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n";
    for (auto &pr : p) {
        cout << pr.pid << "\t" << pr.at << "\t" << pr.bt << "\t"
             << pr.st << "\t" << pr.ct << "\t"
             << pr.tat << "\t" << pr.wt << "\t"
             << pr.rt << "\n";
    }

    cout << "\nAverage TAT = " << (total_tat / n);
    cout << "\nAverage WT  = " << (total_wt / n);
    cout << "\nAverage RT  = " << (total_rt / n) << "\n";

    

    return 0;
}
