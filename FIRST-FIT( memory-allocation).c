#include<stdio.h>

int main(){
     int blockCount, processCount;
     int blockSize[20], processSize[20];
     int allocation[20];

     printf("Enter total blockCount : ");
     scanf("%d", &blockCount);

     printf("Enter size of each blocksize : ");
     for(int i = 0; i < blockCount; i++){
          scanf("%d", &blockSize[i]);
     }

     printf("Enter total processCount : ");
     scanf("%d", &processCount);

     printf("Enter size of each processSize : ");
     for(int i = 0; i < processCount; i++){
          scanf("%d", &processSize[i]);
     }

     for(int i = 0; i < processCount; i++){
          allocation[i] = -1;
     }

     // logic first logic 
     for(int i = 0; i < processCount; i++){
          for(int j = 0; j < blockCount; j++){
               if(blockSize[j] >= processSize[i]){
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    break;
               }
          }
     }

     printf("\nProcess No.\tProcess Size\tBlock No. \n");
     for(int i = 0; i < processCount; i++){
          printf("%d\t\t\t%d\t\t", i + 1, processSize[i]);
          if(allocation[i] != -1){
              printf("%d\n", allocation[i] + 1);
          }
          else{
              printf("No Memory Allocated\n");
          }
    }
}
