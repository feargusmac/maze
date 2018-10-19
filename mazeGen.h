/* 
 * File:   mazeGen.h
 * Author: Feargus
 *
 * Generates a square maze using disjoint sets.
 */

#ifndef MAZEGEN_H
#define MAZEGEN_H

#include "disjointSet.h"
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
    void shuffle(std::vector<int>&);
    
    // helper access functions
    int above(int);
    int right(int);
    int below(int);
    int left(int);
    
    // private variables
    int N; // num cells in one side
    int numCells;
    std::vector<int> indices;
    disjointSet *MazeSets;
    int *Maze;
    
    // CONSTANTS

    int TOP = 8;
    int RIGHTSIDE = 1;
    int BOTTOM = 2;
    int LEFTSIDE = 4;
    
};

#endif /* MAZEGEN_H */

