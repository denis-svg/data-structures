#pragma once
#include <iostream>
template<typename T>
struct DqNode{
    T data;
    DqNode* next;
    DqNode* previous;
    DqNode(T data);
};

template<typename T>
class Dequeue{
    private:
        int len;
        DqNode<T>* rear;
        DqNode<T>* front;
    public:
        Dequeue();
        ~Dequeue();
        bool isEmpty();
        void addFront(T data);
        void addRear(T data);
        T removeFront();
        T removeRear();
        int length();
        void log();
};

template<typename T>
void Dequeue<T>::log(){
    DqNode<T>* current = this->front;
    int index = 0;
    std::cout<<'[';
    while (!this->isEmpty()){
        if (this->len == index + 1){
            std::cout<<current->data;
            break;
        }else{
            std::cout<<current->data<<", ";
        }
        index++;
        current = current->next;
    }
    std::cout<<']'<<std::endl;
}

template<typename T>
DqNode<T>::DqNode(T data){
    this->data = data;
    this->previous = nullptr;
    this->next = nullptr;
}

template<typename T>
Dequeue<T>::Dequeue(){
    this->len = 0;
    this->rear = nullptr;
    this->front = nullptr;
}

template<typename T>
bool Dequeue<T>::isEmpty(){
    return this->front == nullptr;
}

template<typename T>
void Dequeue<T>::addFront(T data){
    DqNode<T>* new_node = new DqNode<T>(data); 
    if (this->len == 0){
        this->front = new_node;
        this->rear = new_node;
    }else{
        new_node->next = this->front;
        this->front->previous = new_node;
        this->front = new_node;
    }
    this->len++;
}

template<typename T>
void Dequeue<T>::addRear(T data){
    DqNode<T>* new_node = new DqNode<T>(data); 
    if (this->len == 0){
        this->front = new_node;
        this->rear = new_node;
    }else{
        new_node->previous = this->rear;
        this->rear->next = new_node;
        this->rear = new_node;
    }
    this->len++;
}

template<typename T>
T Dequeue<T>::removeFront(){
    if (this->isEmpty())
        throw "remove from an empty dequeue";
    else if (this->len == 1){
        T data = this->front->data;
        delete this->front;
        this->front = nullptr;
        this->rear = nullptr;
        this->len--;
        return data;
    }else{
        T data = this->front->data;
        this->front->next->previous = nullptr;
        DqNode<T>* temp = this->front;
        this->front = temp->next;
        delete temp;
        this->len--;
        return data;
    }
}

template<typename T>
T Dequeue<T>::removeRear(){
    if (this->isEmpty())
        throw "remove from an empty dequeue";
    else if (this->len == 1){
        T data = this->rear->data;
        delete this->rear;
        this->front = nullptr;
        this->rear = nullptr;
        this->len--;
        return data;
    }else{
        T data = this->rear->data;
        this->rear->previous->next = nullptr;
        DqNode<T>* temp = this->rear;
        this->rear = temp->previous;
        delete temp;
        this->len--;
        return data;
    }
}

template<typename T>
int Dequeue<T>::length(){
    return this->len;
}