from stack import Stack

def par_checker(expression):
	s = Stack()
	for char in expression:
		if char == "(":
			s.push(char)
		elif char == ")":
			if s.is_empty():
				return False
			else:
				s.pop()
	if s.is_empty():
		return True
	else:
		return False

def split(infix_expression):
	out_list = []
	number = ""
	previous = " "
	for index, char in enumerate(infix_expression):
		if char in '0123456789.':
			number += char
			if previous == ')':
				out_list.append('*')
			if index == len(infix_expression) - 1:
				out_list.append(float(number))
			previous = char
		elif char in '+-*/^':
			if previous != ")":
				out_list.append(float(number))
				number = ""
			out_list.append(char)
			previous = char
		elif char in '()':
			if previous in "0123456789":
				if char == '(':
					out_list.append(float(number))
					out_list.append('*')
					number = ""
				elif char == ')':
					out_list.append(float(number))
					number = ""
			if char == '(' and previous == ')':
				out_list.append('*')
			out_list.append(char)
			previous = char
	return out_list

def infix_to_postfix(tokens):
	op_stack = Stack()
	postfix = []
	prec = {"^": 4, "*" : 3, "/" : 3, "+" : 2, "-" : 2, "(" : 1}
	for token in tokens:
		if isinstance(token, float):
			postfix.append(token)
		elif token == '(':
			op_stack.push(token)
		elif token == ')':
			top_token = op_stack.pop()
			while top_token != '(':
				postfix.append(top_token)
				top_token = op_stack.pop()
		else:
			while (not op_stack.is_empty()):
				if prec[token] <= prec[op_stack.peek()]:
					postfix.append(op_stack.pop())
				else:
					break
			op_stack.push(token)

	while not op_stack.is_empty():
		postfix.append(op_stack.pop())

	return postfix

def postfix_calc(token_list):
	operand_stack = Stack()
	for token in token_list:
		if isinstance(token, float):
			operand_stack.push(token)
		else:
			operand_stack.push(do_math(operand_stack.pop(), operand_stack.pop(), token))

	return operand_stack.pop()

def do_math(operand2, operand1, operator):
	if operator == '+':
		return operand1 + operand2
	elif operator == '-':
		return operand1 - operand2
	elif operator == '/':
		return operand1 / operand2
	elif operator == '*':
		return operand1 * operand2
	elif operator == '^':
		return operand1 ** operand2

def calculate_infix(expression):
	if par_checker(expression):
		token_list = split(expression)
		postfix = infix_to_postfix(token_list)
		return postfix_calc(postfix)
	else:
		raise AttributeError("parantheses are incorect")

from time import time
start = time()
print(calculate_infix("1 + 2 * (20 / 5 )^3 - 434.44 / 21321 + 12"), " : ", (time() - start)*10**6, " microseconds")
start = time()
print(calculate_infix("(21 - 14)(21 + 14)^0.5")," : ", (time() - start)*10**6, " microseconds")
import os
os.chdir("/home/denea/Desktop/datastruct/python/")
start = time()
os.system("exec")
print((time()-start)*10**6)

