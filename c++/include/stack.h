#pragma once
#include <iostream>
template<typename T>
struct Node{
    T data;
    Node* next;
    Node(T data, Node* next);
};
template<typename T>
class Stack{
    private:
        int length;
        Node<T>* top;
    public:
        Stack();
        ~Stack();
        bool is_empty();
        T peek();
        void push(T data);
        T pop();
        void log();
        int get_length() {return this->length;};
};

template<typename T>
Node<T>::Node(T data, Node* next){
    this->data = data;
    this->next = next;
}

template<typename T>
Stack<T>::Stack(){
    this->length = 0;
    this->top = nullptr;
}

template<typename T>
Stack<T>::~Stack(){
    Node<T>* current = this->top;
    while(current != nullptr){
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
bool Stack<T>::is_empty(){
    return this->top == nullptr;
}

template<typename T>
T Stack<T>::peek(){
    return this->top->data;
}

template<typename T>
void Stack<T>::push(T data){
    Node<T>* temp = new Node<T>(data, this->top);
    this->top = temp;
    this->length++;
}

template<typename T>
T Stack<T>::pop(){
    if (this->is_empty())
        throw "pop from an empty stack";
    T data = this->peek();
    Node<T>* temp = this->top;
    this->top = this->top->next;
    this->length--;
    delete temp;
    return data;
}

template<typename T>
void Stack<T>::log(){
     Node<T>* temp = this->top;
     std::cout<<'[';
     int counter = 0;
     while (temp != nullptr){
         if (counter + 1 == this->get_length()){
             std::cout<<temp->data;
             break;
         }
         std::cout<<temp->data<<", ";
         temp = temp->next;
         counter++;
     }   
     std::cout<<']'<<std::endl;
}