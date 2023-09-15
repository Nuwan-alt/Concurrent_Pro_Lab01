//
// Created by jayas on 9/15/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"


void *conMutex_runner(void *rank);

pthread_mutex_t mutex;
node *head;

int insOps_mu;
int delOps_mu;
int memOps_mu;
int thread_count_mu;

unsigned long manage_mutex(int m,int n, float insFrac, float memFrac, float delFrac){
    head = NULL;
    m=m/n;
    insOps_mu = m*insFrac;
    memOps_mu = m*memFrac;
    delOps_mu = m*delFrac;
    thread_count_mu = n;

    srand(time(0));
    int count = 0;
    while (count<1000){
        long value = rand()%65535;
        if(!Member(value, head)){
            Insert(rand()%65535, &head);
            count++ ;
        }

    }

    pthread_mutex_init(&mutex, NULL);
    // Generate Threads
    pthread_t *thread_handles = malloc(thread_count_mu * sizeof(pthread_t));

    struct timeval stop;
    struct timeval start;


    gettimeofday(&start, NULL);
    // print thread count
//    printf("Thread count: %d\n",thread_count_mu);

    for (int thread=0; thread < thread_count_mu ; thread++){
        pthread_create(&thread_handles[thread],NULL,conMutex_runner,(void*) &thread);
    }

    for (int thread=0; thread < thread_count_mu ; thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);

    //Function call
    gettimeofday(&stop, NULL);
    pthread_mutex_destroy(&mutex);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    destructor(head);
//    printf("Mutex ran!\n");
    //print the time taken
//    printf("Mutex took %lu us\n",time);
    return time;
}

void *conMutex_runner(void* rank){
    int ins_mu = 0;
    int mem_mu = 0;
    int del_mu = 0;
    int tot_mu = 0;
    int totOps_mu = insOps_mu + memOps_mu + delOps_mu;

    long my_rank_mu = (long) rank;


    while (tot_mu < totOps_mu){

        int rand_value = rand() % 65535;
        int opp_value = rand() % 3;


        if (ins_mu < insOps_mu && opp_value == 0){
                pthread_mutex_lock(&mutex);
                short res = Insert(rand_value, &head);
                ins_mu++;
                tot_mu++;
                pthread_mutex_unlock(&mutex);
                //printf("Thread %ld Operation %d , Insert %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);

        }
        else if(del_mu < delOps_mu && opp_value == 1){
                pthread_mutex_lock(&mutex);
                short res = Delete(rand_value, &head);
                del_mu++;
                tot_mu++;
                pthread_mutex_unlock(&mutex);
                //printf("Thread %ld Operation %d , Delete %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);
        }

        else if(mem_mu < memOps_mu && opp_value == 2){
                pthread_mutex_lock(&mutex);
                short res = Member(rand_value, head);
                mem_mu++;
                tot_mu++;
                pthread_mutex_unlock(&mutex);
                //printf("Thread %ld Operation %d , Search %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);

        }
    }
//    printf("Hello from thread %d\n",tot_mu);

}
