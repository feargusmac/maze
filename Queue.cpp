/* 
 * File:   Queue.cpp
 * Author: Feargus
 * 
 * A simple queue class for use in mazeSolve.
 */

#include "Queue.h"

template <class T>
Queue<T>::Queue() {
    count = 0;
    queue = new doublyLinkedList();
    
}

template <class T>
Queue<T>::~Queue() {
    delete queue;
}

template <class T>
void Queue<T>::enque(T data) {
    queue->insertRear(data);
    count++;
    return;
}

template <class T>
T Queue<T>::deque() {
    count--;
    return queue->removeFront();
}

template <class T>
bool Queue<T>::isEmpty() {
    return count == 0;
}