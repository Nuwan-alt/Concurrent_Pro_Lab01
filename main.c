#include <stdio.h>

#include "mutex.h"
#include "rw_lock.h"
#include "serial.h"
#include "executer.h"
#include "stat.h"

int main() {
    executer();
    test();
    return 0;
}
