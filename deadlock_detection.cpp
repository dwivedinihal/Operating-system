#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter Number of Processes : ";
    cin >> n;
    int r;
    cout << "Enter Number of Resources : ";
    cin >> r;

    vector<vector<int>> alloc(n, vector<int>(r));
    vector<vector<int>> Maxneed(n, vector<int>(r));
    vector<int> avail(r);

    cout << "\nEnter Maximum requirement of Resources -- \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            cin >> Maxneed[i][j];
        }
    }

    cout << "\nEnter Allocated Resources -- \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            cin >> alloc[i][j];
        }
    }

    vector<vector<int>> remNeed(n, vector<int>(r));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            remNeed[i][j] = Maxneed[i][j] - alloc[i][j];
        }
    }

    vector<int> resource(r);
    cout << "\nResource vectors -- \n";
    for (int j = 0; j < r; j++) {
        cin >> resource[j];
    }

    // calculate available resources 
    for (int j = 0; j < r; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += alloc[i][j];
        }
        avail[j] = resource[j] - sum;
    }

    vector<int> work = avail;
    vector<bool> finish(n, false);
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < r; j++) {
                    if (remNeed[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < r; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    bool DEADLOCK = false;
    for (int i = 0; i < n; i++) {
        if (finish[i] == false) {
            DEADLOCK = true;
            break;
        }
    }
    if (DEADLOCK == true) {
        cout << "DEADLOCK DETECTED \n";
    } else {
        cout << "PROCESS IN SAFE STATE NO DEADLOCK\n";
    }
    return 0;
}
