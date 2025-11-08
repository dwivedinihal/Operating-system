#include<stdio.h>

int main(){
     int blockSize[20];
     int processSize[20];
     int allocation[20];
     int blockCount, processCount;

     printf("Enter Number of blocks : ");
     scanf("%d", &blockCount);

     printf("Enter size of each block : ");
     for(int i = 0; i < blockCount; i++){
          scanf("%d", &blockSize[i]);
     }

     printf("Enter Number of process : ");
     scanf("%d",&processCount);

     printf("Enter size of each process : ");
     for(int i = 0; i < processCount; i++){
          scanf("%d", &processSize[i]);
     }

     // initialize the allocation with -1
     for(int i = 0; i < processCount; i++){
          allocation[i] = -1;
     }

     // best fit logic
     for(int i = 0; i < processCount; i++){
          int bestIdx = -1;
          for(int j = 0; j < blockCount; j++){
               if(blockSize[j] >= processSize[i]){
                    if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx]){
                         bestIdx = j;
                    }
               }
          }
          if(bestIdx != -1){
               allocation[i] = bestIdx;
               blockSize[bestIdx] -= processSize[i];
          }
     }

     printf("\nProcess \tProcess No.\tBlock No. \n");
     for(int i = 0; i < processCount; i++){
          printf("%d\t\t%d\t\t", i+1,processSize[i]);
          if(allocation[i] != -1){
              printf("%d\n", allocation[i] + 1);
          }
          else
          printf("Not Allocated\n");
     }
     return 0;
}