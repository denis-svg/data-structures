#ifndef STACK_H
#define STACK_H
#undef T
#define T char
#include <stdbool.h>
struct SNode{
	T value;
	struct SNode* next;
};

typedef struct Stack{
	struct SNode* top;
	bool (*is_empty)(const struct Stack*);
	T (*peek)(const struct Stack*);
	void (*push)(struct Stack*, T);
	T (*pop)(struct Stack*);
	void (*log)(const struct Stack*);
	int (*len)(const struct Stack*);
} Stack;

extern bool sis_empty(const Stack* s);

extern T speek(const Stack* s);

extern void spush(Stack* s, T data);

extern T spop(Stack* s);

extern void slog(const Stack* s);

extern int slen(const Stack* s);

extern Stack* new_stack();

extern void free_stack(Stack* s);
#undef T
#endif
