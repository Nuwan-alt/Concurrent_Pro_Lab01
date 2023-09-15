cmake_minimum_required(VERSION 3.26)
project(mutex_new C)

set(CMAKE_C_STANDARD 11)

add_executable(mutex_new main.c
        linked_list.c
        linked_list.h
        mutex.c
        mutex.h
        rw_lock.c
        rw_lock.h
        serial.c
        serial.h
        executer.c
        executer.h)
