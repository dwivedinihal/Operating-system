#include<bits/stdc++.h>
using namespace std;

struct Process{
     int pid;     // process id
     int at;      // arrival time
     int bt;      // burst timw
     int pr;      // priority ( lower the number , higher the priority)
     int bt_left; // burst time left
     int ct;      // completion time
     int tat;     // turnaround time
     int wt;      // waiting tim
};

int main(){
     int n;
     cout<<"Enter number of Processes : ";
     cin >> n;
     
     vector<Process> p(n);
     for(int i = 0; i < n; i++){
          p[i].pid = i + 1;
          cout<<"Enter arrival time, burst time, priority of P"<<i+1<<" : ";
          cin >> p[i].at >> p[i].bt >> p[i].pr;
          p[i].bt_left = p[i].bt;
     }

     int completed = 0;
     int time = 0;

     while(completed < n){
          int idx = -1;
          int best_pr = INT_MAX;

          // find the highest priroity process among the arrived ones
          for(int i = 0; i < n; i++){
               if(p[i].at <= time && p[i].bt_left > 0){
                    if(p[i].pr < best_pr){
                         best_pr = p[i].pr;
                         idx = i;
                    }
                    else if(p[i].pr == best_pr){
                         if(p[i].at < p[idx].at) idx = i;
                    }
               }
          }

          if(idx != -1){
               // excute the curr process for the 1 unit time 
               p[idx].bt_left--;
               time++;

               if(p[idx].bt_left == 0){
                    completed++;
                    p[idx].ct = time;
                    p[idx].tat = p[idx].ct - p[idx].at;
                    p[idx].wt = p[idx].tat - p[idx].bt;
               }
          }
          else{
               // no process is ready, then move time by 1 for the current process
               time++;
          }
     }
          double avg_tat = 0.0;
          double avg_wt = 0.0;

          cout<< "\nPID\tAt\tBt\tPr\tCT\tTAT\tWT\n";
          for(auto &it : p){
               cout << "P" << it.pid << "\t" 
               << it.at << "\t"
               << it.bt << "\t" 
               << it.pr << "\t"
               << it.ct << "\t" 
               << it.tat << "\t"
               << it.wt << "\n";

               avg_tat += it.tat;
               avg_wt += it.wt;
          }

          cout<<"\nAverage TurnAround time : "<< avg_tat / n ;
          cout<<"\nAverage Waiting time : "<< avg_wt / n ;
}