#include "readerwriter.h"
lock_t RWlock;

#define THREAD_COUNT 8

void create_threads(char* scenario, pthread_t* threads, int count) {
    for(int i = 0; i < count; i++) {
        if(scenario[i] == 'w') {
            pthread_create(&threads[i], NULL, writer, NULL);
        } else if(scenario[i] == 'r') {
            pthread_create(&threads[i], NULL, reader, NULL);
        }
    }
}

void join_threads(pthread_t* threads, int count) {
    for(int i = 0; i < count; i++) {
        pthread_join(threads[i], NULL);
    }
}

void process_scenarios(FILE* scenarios_file) {
    pthread_t threads[THREAD_COUNT];
    char scenario[THREAD_COUNT];
    int index = 0;
    char action;

    while(fscanf(scenarios_file, "%c", &action) != EOF) {
        if(action == 'w' || action == 'r') {
            scenario[index] = action;
            index++;
        } else if(action == '\n' || action == EOF) {
            create_threads(scenario, threads, index);
            join_threads(threads, index);
            index = 0;
            if(action == EOF)
                break;
        }
    }
    
    // Process remaining scenarios if any
    if(index > 0) {
        create_threads(scenario, threads, index);
        join_threads(threads, index);
    }
}

int main() {
    create_RWlock(&RWlock);

    FILE* scenarios_file = fopen("scenarios.txt", "r");

    if(scenarios_file) {
        process_scenarios(scenarios_file);
    } else {
        printf("Failed to open the file");   
    }

    return 0;
}

