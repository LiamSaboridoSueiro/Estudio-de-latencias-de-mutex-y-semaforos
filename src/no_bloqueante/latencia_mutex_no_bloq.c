/*
gcc -O2 -pthread latencia_mutex_no_bloq.c -o latencia_mutex_no_bloq
./latencia_mutex_no_bloq > latencia_mutex_no_bloq.txt
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#define TOTAL_THREADS 1
#define N 800
#define SECTONANO   1000000000
#define MILISTONANO 1000000

#define MIN_SLEEP_MS 50
#define MAX_SLEEP_MS 100

pthread_mutex_t mutex;
int value = 0;


void* thread_function1 (void) {

    struct timespec begin, end, sleep_time;

    for (int i = 0; i < N; i++) {

        clock_gettime(CLOCK_MONOTONIC, &begin);
        pthread_mutex_lock(&mutex);
        clock_gettime(CLOCK_MONOTONIC, &end);

        value = value + i;
        pthread_mutex_unlock(&mutex);

        int diff = (int)((end.tv_sec - begin.tv_sec) * (long long)SECTONANO
                         + (end.tv_nsec - begin.tv_nsec));
        printf("%d\n", diff);

        // Sleep for a random time between MIN_SLEEP_MS and MAX_SLEEP_MS
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = ((rand() % (MAX_SLEEP_MS - MIN_SLEEP_MS + 1)) + MIN_SLEEP_MS) * (long)MILISTONANO;
        nanosleep(&sleep_time, NULL);
    }

    return NULL;
}

int main (int argc, char* argv[]) {

    pthread_t threads[TOTAL_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < TOTAL_THREADS; i++){
        pthread_create(&threads[i], NULL, (void *)thread_function1, NULL);
    }

    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
