/* 
 * File:   mazeGen.h
 * Author: Feargus
 *
 * Generates a square maze using disjoint sets.
 */

#ifndef MAZEGEN_H
#define MAZEGEN_H

#include "mazeGen.h"
#include <string>
#include <vector>

class mazeGen{
    
public:
    mazeGen();
    mazeGen(int);
    ~mazeGen();
    void generateMaze();
    std::string printMaze();
    
private:
    void breakWall(int, int);
    bool checkBounds(int, int);
    
    // helper access functions
    int top(int);
    int right(int);
    int bottom(int);
    int left(int);
    
    // private variables
    int N; // num cells in one side
    int numCells;
    std::vector<int> indices;
    disjointSet *MazeSets;
    int *Maze;
    
};

#endif /* MAZEGEN_H */
