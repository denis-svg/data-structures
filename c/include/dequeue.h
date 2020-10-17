#ifndef DEQUEUE_H
#define DEQUEUE_H
#undef T
#define T int
#include <stdbool.h>
struct DqNode{
    T data;
    struct DqNode* next;
    struct DqNode* previous;
};

typedef struct Dequeue{
    struct DqNode* front;
    struct DqNode* rear;
    int length;
    bool (*is_empty)(const struct Dequeue*);
    void (*add_front)(struct Dequeue*, T value);
    void (*add_rear)(struct Dequeue*, T value);
    T (*remove_rear)(struct Dequeue*);
    T (*remove_front)(struct Dequeue*);
    void (*log)(const struct Dequeue*);
    int (*len)(const struct Dequeue*);

}Dequeue;

extern bool dqis_empty(const struct Dequeue*);
extern void dqadd_front(struct Dequeue*, T value);
extern void dqadd_rear(struct Dequeue*, T value);
extern T dqremove_front(struct Dequeue*);
extern T dqremove_rear(struct Dequeue*);
extern void dqlog(const struct Dequeue*);
extern int dqlen(const struct Dequeue*);
extern Dequeue* new_dequeue();
extern void free_dequeue(struct Dequeue*);
#endif