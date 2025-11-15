#include<stdio.h>
#include<stdbool.h>

typedef struct file{
     char name;
     int idxBlock;   // start block
     int blockCount;
     int blocks[1000];
} File;

int main(){
     int n;
     printf("Enter number of files : ");
     scanf("%d", &n);

     bool Freeblock[1000];
     for(int i = 0; i < 1000; i++){
          Freeblock[i] = true; // initally all the blocks are free
     }

     File files[n];

     for(int i = 0; i < n; i++){
          getchar();

          printf("Enter file name %d : ", i + 1);
          scanf("%c", &files[i].name);

          printf("Enter start block of file %d : ", i + 1);
          scanf("%d", &files[i].idxBlock);

          printf("Enter Number of blocks required for a file %d : ", i + 1);
          scanf("%d", &files[i].blockCount);

          // alloacte the blocks that are free
          printf("Enter blocks that are allocated : ");
          for(int j = 0; j < files[i].blockCount; j++){
               int b;

               while(1){
                    scanf("%d", &b);

                    if(b < 0 || b >= 1000){
                         printf("INVALID BLOCK\n");
                    }
                    else if(Freeblock[b] == false){
                         printf("Block already occupied \n");
                    }
                    else{
                         files[i].blocks[j] = b;
                         Freeblock[j] = false;
                         break;
                    }
               }
          }
     }

     // search for a file
     char sc;
     bool found = false;
     getchar();
     printf("Enter file to serach for : ");
     scanf("%c", &sc);

     for(int i = 0; i < n; i++){
          if(files[i].name == sc){
               printf("File found \n");

               printf("----------------------------------\n");
               printf("File name        : %c\n", files[i].name);
               printf("Start block      : %d\n", files[i].idxBlock);
               printf("Total blokcs     : %d\n", files[i].blockCount);

               printf("Blocks alloacted : ");
               for(int j = 0; j < files[i].blockCount; j++){
                    printf("%d ", files[i].blocks[j]);
               }

               printf("\n");
               found = true;
               break;
          }
     }
     if(!found){
          printf("Not found \n");
     }
}