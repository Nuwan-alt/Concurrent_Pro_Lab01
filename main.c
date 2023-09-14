#include <stdio.h>

#include "mutex.h"
#include "rw_lock.h"
#include "serial.h"

int main() {

    unsigned long mut_t8_runtime, re_t8_runtime, serial_runtime;
    FILE *fp;
    fp = fopen("../output/Case_1.csv","a");


    mut_t8_runtime = manage_mutex(10000,8,0.005,0.99,0.005);
    re_t8_runtime = manage_rw(10000,8,0.005,0.99,0.005);
    serial_runtime = manage_serial(10000,0.005,0.99,0.005);

//    printf("mutex %lu\n", mut_t8_runtime);
//    printf("rw %lu\n", re_t8_runtime);
//    printf("serial %lu\n", serial_runtime);



    fprintf(fp, "%lu %lu %lu\n", mut_t8_runtime, re_t8_runtime, serial_runtime);

    fclose(fp);
    return 0;

}
