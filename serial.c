//
// Created by jayas on 9/15/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"

void *conSerial_runner();
node *head_se;

int insOps_se;
int delOps_se;
int memOps_se;

unsigned long manage_serial(int m, float insFrac, float memFrac, float delFrac){
    head_se = NULL;
    insOps_se = m*insFrac;
    memOps_se= m*memFrac;
    delOps_se = m*delFrac;

    srand(time(0));
    int count = 0;
    int n = 1000;
    while (count<n){
        long value = rand()%65535;
        if(!Member(value, head_se)){
            Insert(rand()%65535, &head_se);
            count++ ;
        }

    }

    struct timeval stop;
    struct timeval start;


    gettimeofday(&start, NULL);

    conSerial_runner();

    //Function call
    gettimeofday(&stop, NULL);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    destructor(head_se);
//    printf("Serial ran!\n");

//    printf("Serial took %lu us\n",time);
    return time;
}

void *conSerial_runner(){
    int ins_se = 0;
    int mem_se = 0;
    int del_se = 0;
    int tot_se = 0;
    int totOps_se = insOps_se + memOps_se + delOps_se;


    while (tot_se < totOps_se){

        int rand_value = rand() % 65535;


        if (ins_se < insOps_se){
            short res = Insert(rand_value, &head_se);
            ins_se++;
            tot_se++;
            //printf("Thread %ld Operation %d , Insert %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);

        }
        else if(del_se < delOps_se){
            short res = Delete(rand_value, &head_se);
            del_se++;
            tot_se++;

            //printf("Thread %ld Operation %d , Delete %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);
        }

        else if(mem_se < memOps_se){
            short res = Member(rand_value, head_se);
            mem_se++;
            tot_se++;

            //printf("Thread %ld Operation %d , Search %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);

        }
    }
//    printf("Hello from thread %d\n",tot_se);

}
