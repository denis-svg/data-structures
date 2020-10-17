#pragma once
#include <iostream>
template<typename T>
struct SNode{
    T data;
    SNode* next;
    SNode(T data, SNode* next);
};
template<typename T>
class Queue{
    private:
        int length;
        SNode<T>* head;
        SNode<T>* top;
    public:
        Queue();
        ~Queue();
        bool is_empty();
        T peek();
        void push(T data);
        T pop();
        void log();
        int get_length() {return this->length;};
};

template<typename T>
SNode<T>::SNode(T data, SNode* next){
    this->data = data;
    this->next = next;
}

template<typename T>
Queue<T>::Queue(){
    this->length = 0;
    this->top = nullptr;
    this->head = nullptr;
}

template<typename T>
Queue<T>::~Queue(){
    SNode<T>* current = this->top;
    while (current != nullptr){
        SNode<T>* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
bool Queue<T>::is_empty(){
    return this->top == nullptr;
}

template<typename T>
T Queue<T>::peek(){
    return this->top->data;
}

template<typename T>
void Queue<T>::push(T data){
    SNode<T>* temp = new SNode<T>(data, nullptr);
    if (this->is_empty()){
        this->head = temp;
        this->top = temp;
    }else {
        this->head->next = temp;
        this->head = temp;
    }
    this->length++;
}

template<typename T>
T Queue<T>::pop(){
    if (this->is_empty())
        throw "pop from an empty queue";
    T data = this->peek();
    SNode<T>* temp = this->top;
    this->top = this->top->next;
    this->length--;
    delete temp;
    return data;
}

template<typename T>
void Queue<T>::log(){
     SNode<T>* temp = this->top;
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
