/*
 * File:   Graph.h
 * Author: Feargus
 *
 * Simple graph class used in Breadth First Search
 * to solve maze.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>

// COLORS as constants
int const WHITE = 0;
int const GREY = 1;
int const BLACK = 2;

class Graph {
    
    
public:
    Graph(int size);
    virtual ~Graph();
    int getSize() const { return size;} 
    int getRow(int) const;
    int getColumn(int) const;
    int getIndex(int, int) const;
    int top(int);
    int right(int);
    int bottom(int);
    int left(int);
    
    std::string *mazeArray; // a string array with number of strings
                    // equal to number of characters in a line, assuming
                    // nxn size maze
    int *color;
    int *parent;
    int *distance;
    
private:
    int size;

};

#endif /* GRAPH_H */

