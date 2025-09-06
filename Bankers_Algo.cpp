#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout << "Enter Number of Processes : ";
    cin >> n;
    cout << "Enter Number of Resources : ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));   // Allocation matrix
    vector<vector<int>> maxNeed(n, vector<int>(m)); // Maximum demand matrix
    vector<int> avail(m);                           // Available resources

    cout << "\nEnter Resources Allocated to processes : \n";
    for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
              cin >> alloc[i][j];
          }
    }

    cout << "\nEnter Maximum Need of Resources for processes : \n";
    for (int i = 0; i < n; i++){
          for (int j = 0; j < m; j++){
               cin >> maxNeed[i][j];
          }
    }

    cout << "\nEnter Available Resources : \n";
    for (int i = 0; i < m; i++){
        cin >> avail[i];
    }

    // Calculate Remaining Need = MaxNeed - Allocation
    vector<vector<int>> remNeed(n, vector<int>(m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            remNeed[i][j] = maxNeed[i][j] - alloc[i][j];
            if (remNeed[i][j] < 0){
                   return 0;
            }
        }
    }

    vector<int> safeSeq;        // Store safe sequence
    vector<bool> finish(n, false);
    vector<int> work = avail;   // Work = currently available resources
    int finishedCount = 0;

    // Repeat until all processes finish or no progress can be made
    while (finishedCount < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;

                // Check if current process can be satisfied
                for (int j = 0; j < m; j++) {
                    if (remNeed[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    // Simulate execution: release resources
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq.push_back(i);
                    finish[i] = true;
                    finishedCount++;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is in DEADLOCK state!\n";
            return 0;
        }
    }

    // If all processes finished → Safe sequence found
    cout << "\nSystem is in SAFE STATE.\nSafe Sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
