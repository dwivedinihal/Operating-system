#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty; // seamphore to count the empty slots
sem_t full; // seamphore to count the filled slots
pthread_mutex_t mutex; 

void* producer(void* arg){
     while(1){
          int item = rand() % 100;

          sem_wait(&empty); // wait for the empty slots 
          pthread_mutex_lock(&mutex); // loct the critical section for proudcer

          buffer[in] = item;
          printf("Proudced item : %d at %d\n", item, in);
          in = (in + 1) % BUFFER_SIZE;

          pthread_mutex_unlock(&mutex);
          sem_post(&full);
          sleep(1);
     }
     return NULL;
}

void* consumer(void* arg){
     while(1){
          sem_wait(&full); // wait for production
          pthread_mutex_lock(&mutex);

          int item = buffer[out];
          printf("Consumed item : %d at %d\n", item, out);
          out = (out + 1) % BUFFER_SIZE;

          pthread_mutex_unlock(&mutex);
          sem_post(&empty);
          sleep(1);
     } 
     return NULL;
}

int main(){
     pthread_t prod, cons;

     sem_init(&empty, 0, BUFFER_SIZE);
     sem_init(&full, 0, 0);
     pthread_mutex_init(&mutex, NULL);

     pthread_create(&prod, 0, producer, NULL);
     pthread_create(&cons, 0, consumer, NULL);

     pthread_join(prod, NULL);
     pthread_join(cons, NULL);

     sem_destroy(&empty);
     sem_destroy(&full);
     pthread_mutex_destroy(&mutex);

     return 0;
}
