//
// Created by jayas on 9/15/2023.
//

#ifndef MUTEX_NEW_LINKED_LIST_H
#define MUTEX_NEW_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node {
    int data;
    struct node * next;
    pthread_mutex_t mutex;
};

typedef struct node node;

void destructor(node* head_p);
int Member(int value, node *head_p);
int Insert(int value, node **head_p);
int Delete(int value, node **head_p);
void Print(node * head_p);



#endif //MUTEX_NEW_LINKED_LIST_H
