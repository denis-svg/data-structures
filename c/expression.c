#include <stdio.h>
#include "include/strqueue.h"
#include "include/stack.h"
#include "include/strstack.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static void to_char_array(const char* c, char* a){
	const char* d = c;
	int index = 0;
	while (*d != '\0'){
		a[index] = *d;
		index++;
		d++;
	}
	a[index] = '\0';
}

static char* copy(char * number, int index){
	char * num = (char*)malloc(index + 1);
	char * copy = num;
	while (*number != '\0'){
		*num = *number;
		num++;
		number++;
	}
	return copy;
}

static bool is_in(char chr, char* str){
	char* schr = str;
	while (*schr != '\0'){
		if (*schr == chr)
			return true;
		schr = schr + 1;
	} 
	return false;
}

static char* do_math(char* operand1, char* operand2, char* operator){
	char op = operator[0];
	char *ptr1;
	char *ptr2;
	char o1[17];
	char o2[17];
	to_char_array(operand1, o1);
	to_char_array(operand2, o2);
	long double opr1 = strtold(o1, &ptr1);
	long double opr2 = strtold(o2, &ptr2);
	long double result;
	char out[17];
	switch (op)
	{
	case '+':
		result = opr1 + opr2;
		snprintf(out, 17, "%Lf", result);
		return copy(&out[0], 16);
	case '-':
		result = opr1 - opr2;
		snprintf(out, 17, "%Lf", result);
		return copy(&out[0], 16);
	case '*':
		result = opr1 * opr2;
		snprintf(out, 17, "%Lf", result);
		return copy(&out[0], 16);
	case '/':
		result = opr1/opr2;
		snprintf(out, 17, "%Lf", result);
		return copy(&out[0], 16);
	case '^':
		result = powl(opr1, opr2);
		snprintf(out, 17, "%Lf", result);
		return copy(&out[0], 16);
	default:
		fprintf(stderr, "invalid operand");
		exit(1);
	}
}

static bool par_checker(char* expression){
	char* chr = expression;
	Stack *s = new_stack();
	while (*chr != '\0'){
		if (*chr == '(')
			s->push(s, *chr);
		else if (*chr == ')') {
			if (s->is_empty(s)){
				free_stack(s);
				return false;
			}
			else
				s->pop(s);
		}
		chr++;
	}
	if (s->is_empty(s)){
		free_stack(s);
		return true;
	}
	else {
		free_stack(s);
		return false;
	}
}

static StrQueue* split(char* expression){
	StrQueue* q = new_strqueue();
	char* chr = expression;
	char operand[2];
	char number[17];
	int index = 0;
	char previous = ' ';
	while(*chr != '\0'){
		if (is_in(*chr, "01234567890.")){
			number[index] = *chr;
			index++;
			if (previous == ')')
				q->push(q, copy("*", 1));
			chr++;
			if(*chr == '\0'){
				number[index] = '\0';
				q->push(q, copy(&number[0], index));
				break;
			}
			chr--;
			previous = *chr;
		}else if (is_in(*chr, "()")){
			if (is_in(previous, "0123456789")){
				if (*chr == '('){
					number[index] = '\0';
					q->push(q, copy(&number[0], index));
					index = 0;
					q->push(q, copy("*", 1));
				}else if (*chr == ')'){
					number[index] = '\0';
					q->push(q, copy(&number[0], index));
					index = 0;
				}

			}else if (*chr == '(' && previous == ')'){
				q->push(q, copy("*", 1));
			}
			char operand[2] = {*chr, '\0'};
			q->push(q, copy(&operand[0], 1));
			previous = *chr;
			}else if (is_in(*chr, "-+*/^")){
				if (previous != ')'){
					number[index] = '\0';
					q->push(q, copy(&number[0], index));
					index = 0;
				}
				char operand[2] = {*chr, '\0'};
				q->push(q, copy(&operand[0], 1));
				previous = *chr;
			}
		chr++;
	}
	return q;
}

static int get_prec(char* op){
	char cop = op[0];
	switch (cop)
	{
	case '^':
		return 4;
	case '*':
		return 3;
	case '/':
		return 3;
	case '+':
		return 2;
	case '-':
		return 2;
	case '(':
		return 1;
	default:
		fprintf(stderr, "invalid symbol\n");
		exit(1);
	}
}

static StrQueue* infix_to_postfix(StrQueue* q){
	StrStack* op_stack = new_strstack();
	StrQueue* out = new_strqueue();
	while(!q->is_empty(q)){
		char* token = q->pop(q);
		if (is_in(token[0], "0123456789"))
			out->push(out, token);
		else if (token[0] == '(')
			op_stack->push(op_stack, token);
		else if (token[0] == ')'){
			char* top_token = op_stack->pop(op_stack);
			while(top_token[0] != '('){
				out->push(out, top_token);
				top_token = op_stack->pop(op_stack);
			}
			free(top_token);
			free(token);
		}
		else{
			while (!op_stack->is_empty(op_stack)){
				if (get_prec(token) <= get_prec(op_stack->peek(op_stack)))
					out->push(out, op_stack->pop(op_stack));
				else
					break;
			}		
			op_stack->push(op_stack, token);
		}
	}
	while (!op_stack->is_empty(op_stack)){
		out->push(out, op_stack->pop(op_stack));
	}
	free_strstack(op_stack);
	free_strqueue(q);
	return out;
} 

static char* postfix_cal(StrQueue* q){
	StrStack* operand_stack = new_strstack();
	while(!q->is_empty(q)){
		char* token = q->pop(q);
		if (is_in(token[0], "0123456789"))
			operand_stack->push(operand_stack, token);
		else{
			char * operand1 = operand_stack->pop(operand_stack);
			char * operand2 = operand_stack->pop(operand_stack);
			operand_stack->push(operand_stack, do_math(operand2, operand1, token));
			free(token);
			free(operand1);
			free(operand2);
		}
	}
	char* res = operand_stack->pop(operand_stack);
	free_strqueue(q);
	free_strstack(operand_stack);
	return res;
}

static long double calculate(char * expression){
	if (par_checker(&expression[0])){
		StrQueue* q = split(&expression[0]);
		StrQueue* a = infix_to_postfix(q);
		char * result = postfix_cal(a);
		char * ptr;
		long double res = strtold(result, &ptr);
		free(result);
		return res;
	}else{
		fprintf(stderr, "incorect paranthesis");
		exit(1);
	}
}

int main(){
    time_t start = clock();
	printf("%Lf : %lf microseconds\n", calculate("1 + 2 * (20 / 5 )^3 - 434.44 / 21321 + 12"), (double)(clock() - start)/CLOCKS_PER_SEC*1000000);
	start = clock();
	printf("%Lf : %lf microseconds\n", calculate("(21 - 14)(21 + 14)^0.5"), (double)(clock() - start)/CLOCKS_PER_SEC*1000000);
}
