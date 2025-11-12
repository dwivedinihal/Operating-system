#include<stdio.h>
#include<stdbool.h>

typedef struct file{
     char name;
     int start_block;
     int blocks[100]; // list of blocks are linked 
     int no_blocks;
}File;

int main(){
     bool blocks[1000];
     for(int i = 0; i < 1000; i++){
          blocks[i] = true; // initally all the blocks are free
     }

     int n;
     printf("Enter number of files : ");
     scanf("%d", &n);

     File files[n];

     for(int i = 0; i < n; i++){
          getchar();

          printf("Enter file name %d\n : ", i + 1);
          scanf("%c", &files[i].name);

          printf("Enter start block of file %d\n: ", i + 1);
          scanf("%d", &files[i].start_block);

          printf("Enter number of blocks for file %d\n :", i + 1);
          scanf("%d", &files[i].no_blocks);

          printf("Enter block number for file %d\n: ", i + 1);

          // allocate the blocks for file
          for(int j = 0; j < files[i].no_blocks; j++){
               int b;
               while(1){
                    scanf("%d", &b);

                    if(b < 0 || b >= 1000){
                         printf("invalid blocks.\n");
                    }
                    else if(blocks[b] == false){
                         printf("blocks is already occupied and not free.\n");
                    }
                    else{
                         files[i].blocks[j] = b;
                         blocks[b] = false; // mark as occupied
                         break;
                    }
               }
          }
     }

     char ch;
     getchar();
     printf("Enter file name for searching : ");
     scanf("%c", &ch);

     bool found = false;

     for(int i = 0; i < n; i++){
          if (files[i].name == ch) {
               printf("\n File Found!\n");
               printf("----------------------------\n");
               printf("File Name        : %c\n", files[i].name);
               printf("Start Block      : %d\n", files[i].start_block);
               printf("Number of Blocks : %d\n", files[i].no_blocks);
               printf("Blocks (Linked)  : ");

               // Print linked block chain
               for (int j = 0; j < files[i].no_blocks; j++) {
                   printf("%d -> ", files[i].blocks[j]);
               }
               printf("NULL\n");
               printf("----------------------------\n");

               found = true;
               break;
          }
     }

     if(!found){
          printf("file not found\n");
     }
}