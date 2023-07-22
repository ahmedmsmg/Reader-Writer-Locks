#ifndef READERWRITER
#define READERWRITER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
    int readers;
    sem_t mutex;
    sem_t wrtlock;
    sem_t queue;  // This semaphore will act as our turnstile
} lock_t;

extern lock_t RWlock;

void reading_writing();
void create_RWlock(lock_t *RWlock);
void rwlock_acquire_readlock(lock_t *RWlock);
void rwlock_release_readlock(lock_t *RWlock);
void rwlock_acquire_writelock(lock_t *RWlock);
void rwlock_release_writelock(lock_t *RWlock);
void* reader(void* args);
void* writer(void* args);

#endif
