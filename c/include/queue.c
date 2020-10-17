#include "strqueue.h"
#include <stdlib.h>
#include <stdio.h>

extern bool strqis_empty(const StrQueue* q){
	return q->top == NULL;
}

extern char* strqpeek(const StrQueue* q){
	if (strqis_empty(q)){
		fprintf(stderr, "peek from an empty queue\n");
		exit(1);
	}
	return q->top->value;
}

extern void strqpush(StrQueue* q, char* data){
	struct StrQNode* temp = (struct StrQNode*)malloc(sizeof(struct StrQNode));
	temp->value = data;
	temp->next = NULL;
	if (strqis_empty(q)){
		q->top = temp;
		q->head = temp;
	}else{
		(q->head)->next = temp;
		(q->head) = temp;
	}
}

extern char* strqpop(StrQueue* q){
	struct StrQNode* temp;
	if (strqis_empty(q)){
		fprintf(stderr, "pop from an empty queue\n");
		exit(1);
	}else{
		char* data = (q->top)->value;
		temp = q->top;
		q->top = (q->top)->next;
		free(temp);
		return data;
	}
}

extern void strqlog(const StrQueue* q){
	struct StrQNode* current = q->top;
	printf("[");
	int length = strqlen(q);
	int index = 0;
	while (current != NULL){
		if (index + 1 != length)
			printf("\"%s\", ", current->value);
		else
			printf("\"%s\"", current->value);
		current = current->next;
		index++;
	}
	printf("]\n");
}

extern int strqlen(const StrQueue* q){
	struct StrQNode* current = q->top;
	int length = 0;
	while (current != NULL){
		length++;
		current = current->next;
	}
	return length;
}

extern StrQueue* new_strqueue(){
	StrQueue* q = (StrQueue*)malloc(sizeof(StrQueue));
	q->head = NULL;
	q->top = NULL;
	q->is_empty = &strqis_empty;
	q->peek = &strqpeek;
	q->push = &strqpush;
	q->pop = &strqpop;
	q->log = &strqlog;
	q->len = &strqlen;
	return q;
} 
extern void free_strqueue(StrQueue* q){
	while (!strqis_empty(q)){
		strqpop(q);
	}
	free(q);
}