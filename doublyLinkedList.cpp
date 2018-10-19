/* 
 * File:   doublyLinkedList.cpp
 * Author: Feargus
 * 
 * A simple doubly linked list class for use in the Queue class.
 */

#include "doublyLinkedList.h"
#include <iostream>

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