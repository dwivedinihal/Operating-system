#include<stdio.h>
int main(){
     int pages[50];
     int frames[50];
     // int temp[50];

     int total_pages = 0;
     int total_frames = 0;

     int page_Faults = 0;
     int pointer = 0;

     printf("Enter total pages : ");
     scanf("%d", &total_pages);

     printf("Enter page referrence string : ");
     for(int i = 0; i < total_pages; i++){
          scanf("%d", &pages[i]);
     }

     printf("Enter total frames : ");
     scanf("%d", &total_frames);

     // initilaize the frames with -1
     for(int i = 0; i < total_frames; i++){
          frames[i] = -1;
     }

     printf("\nPage\tFrames\t\tPage Fault\n");
     printf("-------------------------------------\n");
     // logic for FIFO
     for(int i = 0; i < total_pages; i++){
          int flag = 0; // for checking if the page is laready present in frame or not
          for(int j = 0; j < total_frames; j++){
               if(frames[j] == pages[i]){
                    flag = 1;
                    break;
               }
          }
          if(flag == 0){
               frames[pointer] = pages[i];
               pointer = (pointer + 1) % total_frames;
               page_Faults++;

               printf("%d\t", pages[i]);
               for(int j = 0; j < total_frames; j++)
                   printf("%d ", frames[j]);
               printf("\t Yes\n");
          }
          else{
               printf("%d\t", pages[i]);
               for(int j = 0; j < total_frames; j++)
                   printf("%d ", frames[j]);
               printf("\t No\n");
          }
     }
     printf("\nTotal Page Faults = %d\n", page_Faults);
}