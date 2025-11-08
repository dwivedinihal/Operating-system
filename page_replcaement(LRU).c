#include<stdio.h>

int main(){
     int frames[10];
     int pages[50];
     int counter[10];

     int total_pages;
     int total_frames;

     int page_faults = 0, time = 0;

     printf("Enter total pages : ");
     scanf("%d", &total_pages);

     printf("Enter referrence string : ");
     for(int i = 0; i < total_pages; i++){
          scanf("%d", &pages[i]);
     }

     printf("Enter total frames : ");
     scanf("%d", &total_frames);

     for(int i = 0; i < total_frames; i++){
          frames[i] = -1;
          counter[i] = 0;
     }

     printf("\nPage\tFrames\t\tPage Fault\n");
     
     // LRU logic
     for(int i = 0; i < total_pages; i++){
          int flag = 0; // flag = 1 , means hit, no page replacement required

          // check if the page is already present or not
          for(int j = 0; j < total_frames; j++){
               if(frames[j] == pages[i]){
                    time++;            // increase the global clock
                    counter[j] = time; // store the last used frame
                    flag = 1;          // page hit, no page fault
                    break;
               }
          }
          // if page not found, page fault occurs
          if(flag == 0){
               int min = 0;

               // find the frames with least recently used
               for(int j = 1; j < total_frames; j++){
                    if(counter[j] < counter[min]){
                         min = j;
                    }
               }

               // replace the frame
               time++;
               frames[min] = pages[i]; // place new frame int that frame
               counter[min] = time;      // upadate the usage time
               page_faults++;

               printf("%d\t", pages[i]);
               for(int j = 0; j < total_frames; j++){
                    printf("%d ", frames[j]);
               }
               printf("\t YES\n");
          }
          else{
               printf("%d\t", pages[i]);
               for(int j = 0; j < total_frames; j++){
                    printf("%d ", frames[j]);
               }
               printf("\t NO\n");
          }
     }
     // Final result
     printf("\nTotal Page Faults = %d\n", page_faults);
}