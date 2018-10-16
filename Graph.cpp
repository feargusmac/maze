/* 
 * File:   Graph.cpp
 * Author: Feargus
 * 
 * Simple graph class used in Breadth First Search
 * to solve maze.
 * 
 */

#include "Graph.h"
#include <climits>


Graph::Graph(int SIZE) {
    size = SIZE;
    int length = size * size;
    color = new int[length];
    distance = new int[length];
    parent = new int[length];
    mazeArray = new std::string[length];
    
    for (int i = 0; i < length; i++) {
        color[i] = WHITE;
        distance[i] = INT_MAX;
        parent[i] = 0;
    }
}

Graph::~Graph() {
    delete[] color; color = 0;
    delete[] parent; parent = 0;
    delete[] distance; distance = 0;
    delete[] mazeArray; mazeArray = 0;
}

// TODO: bounds check
int Graph::getRow(int index) const {
    return index/size;
}

// TODO: bounds check
int Graph::getColumn(int index) const {
    return index%size;
}

// TODO: bounds check
int Graph::getIndex(int row, int column) const {
    return row*size + column;
}

int Graph::top(int x) {
    if (x-size < 0) return -1;
    return x - size;
}

int Graph::right(int x) {
    if (x%size == size-1) return -1;
    return x+1;
}

int Graph::bottom(int x) {
    if (x+size > (size*size - 1)) return -1;
    return x + size;
}

int Graph::left(int x) {
    if (x%size == 0) return -1;
    return x - 1;
}