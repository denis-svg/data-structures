#include "include/stack.h"
#include <iostream>
#include "include/queue.h"
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <chrono>

static bool par_checker(const std::string& expression){
    Stack<char>* s = new Stack<char>();
    for (int i=0;i < expression.length();i++){
        if (expression[i] == '(')
            s->push(expression[i]);
        else if (expression[i] == ')'){
            if (s->is_empty())
                return false;
            else 
                s->pop();
        }
    }
    if (!s->is_empty()){
        delete s;
        return false;
    }else{
        delete s;
        return true;
    }
}

static std::vector<std::string> split(const std::string& s){
    std::vector<std::string> tokens;
    std::string digits = "0123456789";
    std::string operators = "+-*/^";
    std::string number = "";
    std::string op = "";
    char previous = ' ';
    for (int i = 0;i<s.length();i++){
        if (digits.find(s[i]) != std::string::npos or s[i] == '.'){
            number += s[i];
            if (previous == ')')
                tokens.push_back("*");
            if (i == s.length() - 1){
                tokens.push_back(number);
                number = "";
                break;
            }
            previous = s[i];
        }else if (operators.find(s[i]) != std::string::npos){
            if (digits.find(previous) != std::string::npos){
                tokens.push_back(number);
                number = "";
            }
            op += s[i];
            tokens.push_back(op);
            op = "";
            previous = s[i];
        }else if (s[i] == '('){
            if (digits.find(previous) != std::string::npos){
                tokens.push_back(number);
                number = "";
                tokens.push_back("*");
                tokens.push_back("(");
                previous = s[i];
            }else if (previous == ')'){
                tokens.push_back("*");
                tokens.push_back("(");
                previous = s[i];
            }else{
                tokens.push_back("(");
                previous = s[i];
            }
        }else if(s[i] == ')'){
            if (digits.find(previous) != std::string::npos){
                tokens.push_back(number);
                number = "";
                tokens.push_back(")");
                previous = s[i];
            }else{
                tokens.push_back(")");
                previous = s[i];
            }
        }
    }
    return tokens;
}

static std::vector<std::string> infix_to_postfix(const std::vector<std::string>& infix){
    std::vector<std::string> postfix;
    Stack<std::string>* op = new Stack<std::string>();
    std::map<const char,int> prec;
    std::string numbers = "0123456789";
    prec['^'] = 4; 
    prec['*'] = 3;
    prec['/'] = 3;
    prec['+'] = 2;
    prec['-'] = 2;
    prec['('] = 1;
    for (std::string token : infix){
        if (numbers.find(token[0]) != std::string::npos)
            postfix.push_back(token);
        else if (token[0] == '(')
            op->push(token);
        else if (token[0] == ')'){
            std::string top_token = op->pop();
            while(top_token[0] != '('){
                postfix.push_back(top_token);
                top_token = op->pop();
            } 
        }else{
            while (!op->is_empty()){
                if (prec[token[0]] <= prec[op->peek()[0]])
                    postfix.push_back(op->pop());
                else 
                    break;
            }
            op->push(token);
        }
    }
    while (!op->is_empty()){
        postfix.push_back(op->pop());
    }
    delete op;
    return postfix;
}

static long double do_math(long double operand1, long double operand2, const char& operat){
    switch (operat)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '^':
        return powl(operand1, operand2);
    default:
        throw "invalid operator";
    }
}

static long double postfix_calc(const std::vector<std::string>& postfix_tokens){
    long double result;
    std::string numbers = "0123456789";
    Stack<long double>* operand_stack = new Stack<long double>();
    for (std::string token : postfix_tokens){
        if (numbers.find(token[0]) != std::string::npos){
            operand_stack->push(std::stold(token));
        }else {
            long double operand2 = operand_stack->pop();
            long double operand1 = operand_stack->pop();
            operand_stack->push(do_math(operand1, operand2, token[0]));
        }
    }
    result = operand_stack->pop();
    delete operand_stack;
    return result;
}

static long double calculate_infix(std::string infix_expression){
    if (par_checker(infix_expression)){
    std::vector<std::string>infix_tokens;
    std::vector<std::string>postfix_tokens;
    infix_tokens = split(infix_expression);
    postfix_tokens = infix_to_postfix(infix_tokens);
    return postfix_calc(postfix_tokens);
    }else
        throw "incorrect paranthesis";
}
int main(){
    std::cout<<calculate_infix("1 + 2 * (20 / 5 )^3 - 434.44 / 21321 + 12")<<std::endl;
    std::cout<<calculate_infix("(21 - 14)(21 + 14)^0.5")<<std::endl;
}
