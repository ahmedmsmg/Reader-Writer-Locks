#include "readerwriter.h"
lock_t RWlock;

void reading_writing() {
    int x=0, T = rand()%10000;
    int i;
    for(i = 0; i < T; i++){
        int j;
        for(j = 0; j < T; j++)
            x=i*j;
    }
    return;
}

void create_RWlock(lock_t *RWlock) {
    RWlock->readers = 0;
    sem_init(&RWlock->mutex, 0, 1);
    sem_init(&RWlock->wrtlock, 0, 1);
    sem_init(&RWlock->queue, 0, 1); // Initialize the new semaphore
}

void rwlock_acquire_readlock(lock_t *RWlock) {
    sem_wait(&RWlock->queue);
    sem_wait(&RWlock->mutex);
    RWlock->readers++;
    if (RWlock->readers == 1)
        sem_wait(&RWlock->wrtlock);
    sem_post(&RWlock->mutex);
    sem_post(&RWlock->queue);
}

void rwlock_release_readlock(lock_t *RWlock) {
    sem_wait(&RWlock->mutex);
    RWlock->readers--;
    if(RWlock->readers ==0)
    {
        sem_post(&RWlock->wrtlock);
    }
    sem_post(&RWlock->mutex);
}

void rwlock_acquire_writelock(lock_t *RWlock) {
    sem_wait(&RWlock->queue);
    sem_wait(&RWlock->wrtlock);
}

void rwlock_release_writelock(lock_t *RWlock) {
    sem_post(&RWlock->wrtlock);
    sem_post(&RWlock->queue);
}

void* reader(void* args) {
    rwlock_acquire_readlock(&RWlock);
    printf("Reader's in... reading \n");
    reading_writing();
    rwlock_release_readlock(&RWlock);
    printf("Finished Reading... \n");
    return NULL;
}

void* writer(void* args) {
    rwlock_acquire_writelock(&RWlock);
    printf("Writer's in... writing \n");
    reading_writing();
    rwlock_release_writelock(&RWlock);
    printf("Finished Writing \n");
    return NULL;
}
