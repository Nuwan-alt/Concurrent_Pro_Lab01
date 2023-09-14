//
// Created by jayas on 9/15/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"

void *conRW_runner(void *rank);

pthread_rwlock_t rwlock;
node *head_rw;

int insOps_rw;
int delOps_rw;
int memOps_rw;
int thread_count_rw;

unsigned long manage_rw(int m,int n, float insFrac, float memFrac, float delFrac){
    head_rw = NULL;
    m=m/n;
    insOps_rw = m*insFrac;
    memOps_rw= m*memFrac;
    delOps_rw = m*delFrac;
    thread_count_rw = n;

    srand(time(0));
    int count = 0;
    while (count<1000){
        long value = rand()%65535;
        if(!Member(value, head_rw)){
            Insert(rand()%65535, &head_rw);
            count++ ;
        }

    }

    pthread_rwlock_init(&rwlock, NULL);
    // Generate Threads
    pthread_t *thread_handles = malloc(thread_count_rw * sizeof(pthread_t));

    struct timeval stop;
    struct timeval start;


    gettimeofday(&start, NULL);
    // print thread count
    printf("Thread count: %d\n",thread_count_rw);

    for (int thread=0; thread < thread_count_rw ; thread++){
        pthread_create(&thread_handles[thread],NULL,conRW_runner,(void*) &thread);
    }

    for (int thread=0; thread < thread_count_rw ; thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);

    //Function call
    gettimeofday(&stop, NULL);
    pthread_rwlock_destroy(&rwlock);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    destructor(head_rw);
    printf("Mutex ran!\n");
    //print the time taken
    printf("Mutex took %lu us\n",time);
    return time;
}



void *conRW_runner(void* rank){
    int ins_rw = 0;
    int mem_rw = 0;
    int del_rw = 0;
    int tot_rw = 0;
    int totOps_rw = insOps_rw + memOps_rw + delOps_rw;

    long my_rank = (long) rank;

    while (tot_rw < totOps_rw){

        int rand_value = rand() % 65535;


        if (ins_rw < insOps_rw){
            pthread_rwlock_wrlock(&rwlock);
            short res = Insert(rand_value, &head_rw);
            pthread_rwlock_unlock(&rwlock);
            ins_rw++;
            tot_rw++;
            //printf("Thread %ld Operation %d , Insert %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);

        }
        else if(del_rw < delOps_rw){
            pthread_rwlock_wrlock(&rwlock);
            short res = Delete(rand_value, &head_rw);
            pthread_rwlock_unlock(&rwlock);
            del_rw++;
            tot_rw++;

            //printf("Thread %ld Operation %d , Delete %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);
        }

        else if(mem_rw < memOps_rw){
            pthread_rwlock_wrlock(&rwlock);
            short res = Member(rand_value, head_rw);
            pthread_rwlock_unlock(&rwlock);
            mem_rw++;
            tot_rw++;

            //printf("Thread %ld Operation %d , Search %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);

        }
    }
    printf("Hello from thread %d\n",tot_rw);

}
