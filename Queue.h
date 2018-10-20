/* 
 * File:   Queue.h
 * Author: Feargus
 *
 * A simple queue class for use in mazeSolve.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "doublyLinkedList.h"

template <class T>
class Queue : public doublyLinkedList<T> {
public:
    Queue();
    virtual ~Queue();
    void enque(T data);
    T deque();
    bool isEmpty();
    
private:
    doublyLinkedList<T> *queue;
    int count;

};

#endif /* QUEUE_H */

