#include<bits/stdc++.h>
using namespace std;

struct Process{
     int pid; // process id
     int bt; // brust time
     int at; // arrival time
     int rt; // remamining time
     int ct; // completion time
     int tat; // turnaround time
     int wt; // waiting time
};

int main(){
     int n;
     cout<<"Enter Number of process : ";
     cin>>n;

     vector<Process> p(n);
     for(int i = 0; i < n; i++){
          p[i].pid = i + 1;
          cout<<"Enter arrival time of P"<<i+1<<" : ";
          cin>>p[i].at;
          cout<<"Enter burst time of P"<<i+1<<"   : ";
          cin>>p[i].bt;
          p[i].rt = p[i].bt;
     }

     int tq;
     cout<<"Enter time qunatam : ";
     cin>>tq;

     queue<int> q; // queue to store the process indices 
     vector<bool> inqueue(n, false); // to track if a proces is already in the queue or not
     int completed = 0;
     int time = 0;
     float total_tat = 0;
     float total_wt = 0;

     cout << "\nGantt Chart: ";
     while(completed < n){
          // push newly arrived porces in the queue
          for(int i = 0; i < n; i++){
               if(p[i].rt > 0 && p[i].at <= time && !inqueue[i]){
                    q.push(i);
                    inqueue[i] = true;
               }
          }

          // cpu idle and then continue to execute the cureent process
          if(q.empty()){
               time++;
               continue;
          }

          int idx = q.front();
          q.pop();

          cout << "| P" << p[idx].pid << " ";
          if(p[idx].rt > tq){
               time += tq;
               p[idx].rt -= tq;
          }
          else{
               time += p[idx].rt;
               p[idx].ct = time;
               p[idx].tat = p[idx].ct - p[idx].at;
               p[idx].wt = p[idx].tat - p[idx].bt;
               total_tat += p[idx].tat;
               total_wt += p[idx].wt;
               completed++;
               p[idx].rt = 0;
          }
          for(int i = 0; i < n; i++){
               if(p[i].at <= time && p[i].rt > 0 && !inqueue[i]){
                    q.push(i);
                    inqueue[i] = true;
               }
          }

          if(p[idx].rt > 0){
               q.push(idx);
          }
          inqueue[idx] = (p[idx].rt > 0);
     }
     cout << "|\n";
     cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n"; 
     for (int i = 0; i < n; i++) { 
          cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n"; 
     } 
     cout << "\nAverage Turnaround Time = " << (total_tat / n); 
     cout << "\nAverage Waiting Time = " << (total_wt / n) << endl; 
     return 0;
}