#ifndef STRSTACK_H
#define STRSTACK_H
#undef T
#define T char*
#include <stdbool.h>
struct StrSNode{
	T value;
	struct StrSNode* next;
};

typedef struct StrStack{
	struct StrSNode* top;
	bool (*is_empty)(const struct StrStack*);
	T (*peek)(const struct StrStack*);
	void (*push)(struct StrStack*, T);
	T (*pop)(struct StrStack*);
	void (*log)(const struct StrStack*);
	int (*len)(const struct StrStack*);
} StrStack;

extern bool strsis_empty(const StrStack* s);

extern T strspeek(const StrStack* s);

extern void strspush(StrStack* s, T data);

extern T strspop(StrStack* s);

extern void strslog(const StrStack* s);

extern int strslen(const StrStack* s);

extern StrStack* new_strstack();

extern void free_strstack(StrStack* s);
#undef T
#endif
