#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5

sem_t forks[N];
pthread_t philosphers[N];
int philosphers_id[N];

void* dine(void* num){
     int id = *(int*)num;

     while(1){
          printf("Philospher %d is Thinking... \n", id);
          sleep(1);

          sem_wait(&forks[id]);
          printf("Philospher %d picked the left stick %d\n", id, id);

          sem_wait(&forks[(id + 1) % N]);
          printf("Philospher %d picked the right stick %d\n", id, (id + 1) % N);

          printf("Philospher %d started eating.....\n", id);
          sleep(2);

          sem_post(&forks[id]);
          printf("Philospher %d released the left stick %d\n", id , id);

          sem_post(&forks[(id + 1) % N]);
          printf("Philospher %d released the right stick %d\n", id, (id + 1) % N);

          printf("Philosopher %d finished eating & is thinking again...\n\n", id);
          sleep(1);
     }
}

int main(){

     // initialize the fork semaphore
     for(int i = 0; i < N; i++){
          sem_init(&forks[i], 0, 1);
          philosphers_id[i] = i;
     }

     // create philospher threads
     for(int i = 0; i < N; i++){
          pthread_create(&philosphers[i], NULL, dine, &philosphers_id[i]);
     }

     // join threads
     for(int i = 0; i < N; i++){
          pthread_join(philosphers[i], NULL);
     }

     // destory philospher
     for(int i = 0; i < N; i++){
          sem_destroy(&forks[i]);
     }

     return 0;
}