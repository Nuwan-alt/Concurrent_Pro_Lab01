//
// Created by jayas on 9/15/2023.
//
#include <stdio.h>
#include "mutex.h"
#include "rw_lock.h"
#include "serial.h"

double runFractions[3][3] = {{0.005,0.99,0.005},{0.05,0.9,0.05},{0.25,0.5,0.25}};
int numThreads[4] = {1,2,4,8};

void executer(){
    char path[100];

    FILE *fp;

    // Serial execution
    for(int i=0;i<3;i++){
        snprintf(path, sizeof(path), "../results/serial/Serial_Case%d.txt", i + 1);
        fp = fopen(path, "w+");
        printf("Serial Case %d completed\n",i+1);

        for(int j=0;j<385;j++){
            unsigned long serial_runtime;
            serial_runtime = manage_serial(10000,runFractions[i][0],runFractions[i][1],runFractions[i][2]);
            fprintf(fp, "%lu\n",  serial_runtime);

        }


    }
    fclose(fp);

    //mutex execution
    for(int i=0;i<3;i++){


        printf("Mutex Case %d completed\n",i+1);

        for(int  k=0;k<4;k++){
            snprintf(path, sizeof(path), "../results/mutex/Mutex_Case%d_T%d.txt", i + 1,numThreads[k]);
            fp = fopen(path, "w+");
            for(int j=0;j<385;j++){
                unsigned long mutex_runtime;
                mutex_runtime = manage_mutex(10000,numThreads[k],runFractions[i][0],runFractions[i][1],runFractions[i][2]);
                fprintf(fp, "%lu\n",  mutex_runtime);

            }
        }

    }
    fclose(fp);

    //rw_lock execution
    for(int i=0;i<3;i++){

        printf("RW Case %d completed\n",i+1);

        for(int  k=0;k<4;k++){
            snprintf(path, sizeof(path), "../results/rw_lock/RW_Case%d_T%d.txt", i + 1,numThreads[k]);
            fp = fopen(path, "w+");
            for(int j=0;j<385;j++){
                unsigned long re_runtime;
                re_runtime = manage_rw(10000,numThreads[k],runFractions[i][0],runFractions[i][1],runFractions[i][2]);
                fprintf(fp, "%lu\n",  re_runtime);
            }
        }
    }
    fclose(fp);

    printf("======================================== Test Completed ========================================\n");

}
