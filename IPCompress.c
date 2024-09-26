#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// define the ring_buffer,it holds the info to be processed
typedef struct{
    uint8_t buffer[BUFFER_SIZE];
    volatile uint32_t head;
    volatile uint32_t tail;
    pthread_mutex_t lock;
    sem_t full;
    sem_t empty;
}ring_buffer_t;

// we need a function to init the ring buffer, take a ringbuffer pointer as input
void ring_buffer_init(ring_buffer_t* rb){
    rb->head = 0;
    rb->tail = 0;
    pthread_mutex_init(&rb->lock,NULL);
    sem_init(&rb->full,0,0);
    sem_init(&rb->empty,0,BUFFER_SIZE);
}

// handle enqueue and dequeue
int ring_buffer_enqueue(ring_buffer_t* rb, uint8_t* data){
    sem_wait(&rb->empty);
    pthread_mutex_lock(&rb->lock);
    
    rb->buffer[rb->tail] = data;
    rb->tail = (rb->tail+1) % BUFFER_SIZE;

    pthread_mutex_unlock(&rb->lock);
    sem_post(&rb->full);

    return 0;
}

int ring_buffer_dequeue(ring_buffer_t* rb, uint8_t* data){
    sem_wait(&rb->full);
    pthread_mutex_lock(&rb->lock);

    *data = rb->buffer[rb->head];
    rb->head = (rb->head+1) % BUFFER_SIZE;

    pthread_mutex_unlock(&rb->lock);
    sem_post(&rb->empty);

    return 0;
}

void compress_data(uint8_t* data){
    // do compress here
}

void* input_thread(void* arg){
    // data come
    
}

void *compress_thread(void* arg){
    // write data to a specific memory

}


int main(){
    

    return 0;
}