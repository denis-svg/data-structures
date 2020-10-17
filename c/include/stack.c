#include "stack.h"
#include "strstack.h"
#include <stdlib.h>
#include <stdio.h>

extern bool sis_empty(const Stack* s){
	return s->top == NULL;
}

extern char speek(const Stack* s){
	if (sis_empty(s)){
		fprintf(stderr, "peek from an empty stack\n");
		exit(1);
	}
	return s->top->value;
}

extern void spush(Stack* s, char data){
	struct SNode* temp = (struct SNode*)malloc(sizeof(struct SNode));
	temp->value = data;
	temp->next = (s->top);
	(s->top) = temp;
}

extern char spop(Stack* s){
	struct SNode* temp;
	if (sis_empty(s)){
		fprintf(stderr, "pop from an empty stack\n");
		exit(1);
	}else{
		char data = (s->top)->value;
		temp = s->top;
		s->top = (s->top)->next;
		free(temp);
		return data;
	}
}

extern void slog(const Stack* s){
	struct SNode* current = s->top;
	int length = slen(s);
	int index = 0;
	printf("[");
	while (current != NULL){
		if (index + 1 != length)
			printf("'%c', ", current->value);
		else 
			printf("'%c'", current->value);
		index++;
		current = current->next;
	}
	printf("]\n");
}

extern int slen(const Stack* s){
	struct SNode* current = s->top;
	int length = 0;
	while (current != NULL){
		length++;
		current = current->next;
	}
	return length;
}

extern Stack* new_stack(){
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->top = NULL;
	s->is_empty = &sis_empty;
	s->peek = &speek;
	s->push = &spush;
	s->pop = &spop;
	s->log = &slog;
	s->len = &slen;
	return s;
}

extern void free_stack(Stack* s){
	while (!sis_empty(s)){
		spop(s);
	}
	free(s);
}


extern bool strsis_empty(const StrStack* s){
	return s->top == NULL;
}

extern char* strspeek(const StrStack* s){
	if (strsis_empty(s)){
		fprintf(stderr, "peek from an empty stack\n");
		exit(1);
	}
	return s->top->value;
}

extern void strspush(StrStack* s, char* data){
	struct StrSNode* temp = (struct StrSNode*)malloc(sizeof(struct StrSNode));
	temp->value = data;
	temp->next = (s->top);
	(s->top) = temp;
}

extern char* strspop(StrStack* s){
	struct StrSNode* temp;
	if (strsis_empty(s)){
		fprintf(stderr, "pop from an empty stack\n");
		exit(1);
	}else{
		char* data = (s->top)->value;
		temp = s->top;
		s->top = (s->top)->next;
		free(temp);
		return data;
	}
}

extern void strslog(const StrStack* s){
	struct StrSNode* current = s->top;
	printf("[");
	int length = strslen(s);
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

extern int strslen(const StrStack* s){
	struct StrSNode* current = s->top;
	int length = 0;
	while (current != NULL){
		length++;
		current = current->next;
	}
	return length;
}

extern StrStack* new_strstack(){
	StrStack* s = (StrStack*)malloc(sizeof(StrStack));
	s->top = NULL;
	s->is_empty = &strsis_empty;
	s->peek = &strspeek;
	s->push = &strspush;
	s->pop = &strspop;
	s->log = &strslog;
	s->len = &strslen;
	return s;
}

extern void free_strstack(StrStack* s){
	while (!strsis_empty(s)){
		strspop(s);
	}
	free(s);
}