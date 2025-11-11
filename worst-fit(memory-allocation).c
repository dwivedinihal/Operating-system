#include<stdio.h>

int main(){
     int blockSize[20], processSize[20], allocation[20];
     int blockCount, processCount;

     printf("Enter Number of blockCount : ");
     scanf("%d", &blockCount);

     printf("Enter size of each block : ");
     for(int i = 0; i < blockCount; i++){
          scanf("%d", &blockSize[i]);
     }

     printf("Enter Number of processCount : ");
     scanf("%d", &processCount);

     printf("Enter size of each process : ");
     for(int i = 0; i < processCount; i++){
          scanf("%d", &processSize[i]);
     }

     for(int i = 0; i < processCount; i++){
          allocation[i] = -1;
     }

     // WORST - FIT logic
     for(int i = 0; i < processCount; i++){
          int worstIdx = -1;
          for(int j = 0; j < blockCount; j++){
               if(blockSize[j] >= processSize[i]){
                    if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx]){
                         worstIdx = j;
                    }
               }
          }
          if(worstIdx != -1){
               allocation[i] = worstIdx;
               blockSize[worstIdx] -= processSize[i];
          }
     }

     printf("\nProcess No.\tProcess Size \tBlock No. \n");
     for(int i = 0; i < processCount; i++){
          printf("%d\t\t%d\t\t", i+1, processSize[i]);
          if(allocation[i] != -1){
               printf("%d\n", allocation[i] + 1);
          }
          else{
               printf("Not Alloacted.\n");
          }
     }
}