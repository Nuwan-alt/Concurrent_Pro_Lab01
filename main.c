#include <stdio.h>

#include "mutex.h"
#include "rw_lock.h"
#include "serial.h"
#include "executer.h"

int main() {
    serial_executer();
    return 0;
}
