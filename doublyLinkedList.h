/* 
 * File:   doublyLinkedList.h
 * Author: Feargus
 *
 * A simple doubly linked list class for use in the Queue class.
 */

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>

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
     LinkNode *head;
     LinkNode *tail;

};

#endif /* DOUBLYLINKEDLIST_H */

