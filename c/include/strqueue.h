#ifndef STRQUEUE_H
#define STRQUEUE_H
#undef TYPE
#define TYPE char*
#include <stdbool.h>
struct StrQNode{
	TYPE value;
	struct StrQNode* next;
};

typedef struct StrQueue{
	struct StrQNode* top;
	struct StrQNode* head;
	bool (*is_empty)(const struct StrQueue*);
	TYPE (*peek)(const struct StrQueue*);
	void (*push)(struct StrQueue*, TYPE);
	TYPE (*pop)(struct StrQueue*);
	void (*log)(const struct StrQueue*);
	int (*len)(const struct StrQueue*);
} StrQueue;

extern bool strqis_empty(const StrQueue* q);

extern TYPE strqpeek(const StrQueue* q);

extern void strqpush(StrQueue* q, TYPE data);

extern TYPE strqpop(StrQueue* q);

extern void strqlog(const StrQueue* q);

extern int strqlen(const StrQueue* q);

extern StrQueue* new_strqueue();

extern void free_strqueue(StrQueue* q);
#undef TYPE
#endif