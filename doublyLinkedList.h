/* 
 * File:   doublyLinkedList.h
 * Author: Feargus
 *
 * A simple doubly linked list class for use in the Queue class.
 */

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

// Forward class definition
template <class T>
class doublyLinkedList;
    
// LinkNode for internal connection
template <class T>
class LinkNode {
    friend class doublyLinkedList<T>;
 public: 
    LinkNode() {next = prev = 0; data = 0;}
    ~LinkNode() {}
 private:
    LinkNode *next;
    LinkNode *prev;
    T data;
};
    
template <class T>
class doublyLinkedList {
 public:
    doublyLinkedList();
    virtual ~doublyLinkedList();
    void insertFront(T);
    T removeFront();
    void insertRear(T);
    T removeRear();
    void print();
 private:
     LinkNode<T> *head;
     LinkNode<T> *tail;

};

template <class T>
doublyLinkedList<T>::doublyLinkedList() {
    head = tail = NULL;
}

template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
    LinkNode<T> *temp = head;
    
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template <class T>
void doublyLinkedList<T>::insertFront(T _data) {
    LinkNode<T> *newNode = new LinkNode<T>();
    newNode->data = _data;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (!head) { // if list is empty
        head = tail = newNode;
        return;
    }
    
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
}

template <class T>
T doublyLinkedList<T>::removeFront() {
    if (!head) // if list is empty
        return NULL; // TODO: does this really work for all possible T?
    
    LinkNode<T> *deleteNode = head;
    T output = head->data;
    
    if (head == tail) { // if only one node in list
        delete head;
        head = tail = NULL;
        return output;
    }
    
    head = deleteNode->next;
    head->prev = NULL;
    
    delete deleteNode;
    return output;
}

template <class T>
void doublyLinkedList<T>::insertRear(T _data) {
    LinkNode<T> *newNode = new LinkNode<T>();
    newNode->data = _data;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (!head) { // if list is empty
        head = tail = newNode;
        return;
    }
    
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

template <class T>
T doublyLinkedList<T>::removeRear() {
    if (!tail) // if list is empty
        return NULL; // TODO: does this work for all Ts? (see above)
    
    LinkNode<T> *deleteNode = tail;
    T output = tail->data;
    
    if (head == tail) { //if only one node
        delete tail;
        head = tail = NULL;
        return output;
    }
    
    tail = deleteNode->prev;
    tail->next = NULL;
    
    delete deleteNode;
    return output;
}

template <class T>
void doublyLinkedList<T>::print() {
    LinkNode<T> *temp = head;
    while (temp) {
        std::cout << (temp->data) << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

// QUEUE CLASS ---------------------------------------------

template <class T>
class Queue : public doublyLinkedList<T> {
public:
    Queue() {
        count = 0;
        queue = new doublyLinkedList<T>();
    }
    
    virtual ~Queue() { delete queue; }
    
    void enque(T data) {
        queue->insertRear(data);
        count++;
        return;
    }
    
    T deque() {
        count--;
        return queue->removeFront();
    }
    
    bool isEmpty() { return count == 0; }
    
private:
    doublyLinkedList<T> *queue;
    int count;

};

#endif /* DOUBLYLINKEDLIST_H */