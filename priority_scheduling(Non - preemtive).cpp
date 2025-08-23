#include<bits/stdc++.h>
using namespace std;

struct Process{
     int pid;
     int st;
     int at;
     int bt;
     int rt;
     int wt;
     int tat;
     int ct;
     int priority;
};

int main(){
     int n;
     cout<<"Enter number of processes : ";
     cin>>n;
     
     vector<Process> p(n);
     for(int i = 0; i < n; i++){
          p[i].pid = i + 1;
          cout<<"Enter arrival time of P"<< i + 1 <<" : " ;
          cin>>p[i].at;
          cout<<"Enter burst timr of P"<< i + 1 <<"   : " ;
          cin>>p[i].bt;
          cout<<"Enter priority of P"<< i + 1 <<"     : " ;
          cin>>p[i].priority;
     }

     vector<bool>done(n, false);
     int completed = 0;
     int currtime = 0;
     double totalTAT = 0;
     double totalWT = 0;
     double totalRT = 0;

     while(completed < n){
          int idx = -1;
          int max_prior = INT_MIN // higher the number higher will be the priority

          for(int i = 0; i < n; i++){
               if(p[i].at <= currtime && !done[i]){
                    if(p[i].priority > max_prior){
                         max_prior = p[i].priority;
                         idx = i;
                    }
               }
          }

          // cpu idle
          if(idx == -1){
               currtime++;
               continue;
          }

          // execute process at idx
          p[idx].st = currtime;
          p[idx].ct = p[idx].st + p[idx].bt;
          p[idx].tat = p[idx].ct - p[idx].at;
          p[idx].wt = p[idx].tat - p[idx].bt;
          p[idx].rt = p[idx].st - p[idx].at;

          totalTAT += p[idx].tat;
          totalWT += p[idx].wt;
          totalRT += p[idx].rt;

          currtime = p[idx].ct;
          done[idx] = true;
          completed++;
     }

     cout<<"\nPID\tAT\tBT\tPRI\tST\tCT\tTAT\tWT\tRT\n";
     for(auto &pr : p){
          cout << pr.pid << "\t" << pr.at << "\t" << pr.bt << "\t"
             << pr.priority << "\t" << pr.st << "\t" << pr.ct << "\t"
             << pr.tat << "\t" << pr.wt << "\t" << pr.rt << "\n";
     }
     cout << "\nAverage TAT = " << totalTAT / n;
     cout << "\nAverage WT  = " << totalWT / n;
     cout << "\nAverage RT  = " << totalRT / n << "\n";

}