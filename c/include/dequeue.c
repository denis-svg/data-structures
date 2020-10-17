#include "dequeue.h"
#include <stdlib.h>
#include <stdio.h>

extern bool dqis_empty(const struct Dequeue* d){
    return d->front == NULL;
}

extern void dqadd_front(struct Dequeue* d, int value){
    struct DqNode* new_node = (struct DqNode*)malloc(sizeof(struct DqNode));
    new_node->data = value;
    new_node->next = NULL;
    new_node->previous = NULL;
    d->length++;
    if (dqis_empty(d)){
        d->rear = new_node;
        d->front = new_node;
    }else{
        (d->front)->previous = new_node;
        new_node->next = d->front;
        d->front = new_node;
    }
}

extern void dqadd_rear(struct Dequeue* d, int value){
    struct DqNode* new_node = (struct DqNode*)malloc(sizeof(struct DqNode));
    new_node->data = value;
    new_node->next = NULL;
    new_node->previous = NULL;
    d->length++;
    if (dqis_empty(d)){
        d->rear = new_node;
        d->front = new_node;
    }else{
        (d->rear)->next = new_node;
        new_node->previous = d->rear;
        d->rear = new_node;
    }
}

extern int dqremove_front(struct Dequeue* d){
    if (dqis_empty(d)){
        fprintf(stderr, "remove from an empty dequeue\n");
		exit(1);
    }
    if (d->length != 1){
        int data = (d->front)->data;
        (d->front)->next->previous = NULL;
        struct DqNode* temp = d->front;
        d->front = (d->front)->next;
        free(temp);
        d->length--;
        return data;
    }else{
        int data = d->front->data;
        free(d->front);
        d->front = NULL;
        d->rear = NULL;
        return data;
    }
}

extern int dqremove_rear(struct Dequeue* d){
    if (dqis_empty(d)){
        fprintf(stderr, "remove from an empty dequeue\n");
		exit(1);
    }
    if (d->length != 1){
        int data = (d->rear)->data;
        (d->rear)->previous->next = NULL;
        struct DqNode* temp = d->rear;
        d->rear = (d->rear)->previous;
        free(temp);
        d->length--;
        return data;
    }else{
        int data = d->rear->data;
        free(d->rear);
        d->front = NULL;
        d->rear = NULL;
        d->length--;
        return data;
    }    
}

extern int dqlen(const struct Dequeue* d){
    return d->length;
}

extern void dqlog(const struct Dequeue* d){
    struct DqNode* current = d->front;
    int index = 0;
    printf("[");
    while (current != NULL){
        if (index + 1 == d->length){
            printf("%d",current->data);
            break;
        }else{
            printf("%d, ",current->data);
        }
        index++;
        current = current->next;
    }
    printf("]\n");
}

extern Dequeue* new_dequeue(){
    Dequeue* d = (Dequeue*)malloc(sizeof(Dequeue));
    d->front = NULL;
    d->rear = NULL;
    d->length = 0;
    d->is_empty = &dqis_empty;
    d->add_front = &dqadd_front;
    d->add_rear = &dqadd_rear;
    d->remove_front = &dqremove_front;
    d->remove_rear = &dqremove_rear;
    d->len = &dqlen;
    d->log = &dqlog; 
    return d;
}

extern void free_dequeue(struct Dequeue* d){
    struct DqNode* current = d->front;
    while (current != NULL){
        struct DqNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(d);
}