/* 
 * File:   mazeGen.h
 * Author: Feargus
 *
 * Generates a square maze using disjoint sets.
 * 
 */

#include "disjointSet.h"
#include "mazeGen.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>


mazeGen::mazeGen() {
}

mazeGen::mazeGen(int n) {
    // establish private variables
    N = n; // number of cells on one side
    numCells = N*N; // total number of cells
    MazeSets = new disjointSet(numCells);
    Maze = new int[numCells];
    
    srand(time(0)); // seed random, used to shuffle indices
                    // only needs to be done once so here is good
    
    // every cell of the maze is set to closed box
    // except for the first and final cells, which
    // are the beginning and ending of the maze
    for (int i = 0; i < numCells; i++) {
        indices.push_back(i);
        if (i == 0) {
            Maze[i] = 11;
        } else if (i == numCells - 1) {
            Maze[i] = 14;
        } else {
            Maze[i] = 15;
        }
    }
}

mazeGen::~mazeGen() {
    // TODO: check for additional memory leaks
    delete[] Maze; Maze = 0;
    delete MazeSets; MazeSets = 0;
}

// TODO: the biggest thing to do is clean up
// and modularize this function
void mazeGen::generateMaze() {
    shuffle(indices);
    
    int numUnions = 0;
    int index = 0; 
    while (numUnions < numCells - 1) { // when numUnions = numCells - 1 everything is in union
        // random cell to work with from randomly shuffled vector of all indices
        int currentCell = indices[index];
        
        // instead of rand could have a vector of [TOP, BOTTOM, RIGHT, LEFT] and shuffle that and iterate through
        int wallToBreak = pow(2,(rand()%4)); // randomly select a wall to break
        bool canBreakWall = checkBounds(currentCell, wallToBreak);
        for (int i = 1; i < 4; i++) { // find a wall to break that works
            if (!canBreakWall) {
                if (wallToBreak == 8)
                    wallToBreak = 1;
                else 
                    wallToBreak *= 2;
            
                canBreakWall = checkBounds(currentCell, wallToBreak);
            }
        }
        
        if (canBreakWall) {
            breakWall(currentCell, wallToBreak);
            numUnions++;
        }  
        
        index++;
        if (index == indices.size()) { // if we've been through all the indices and not everything is in union
            index = 0;
        } 
    }
}

// rename toString?
std::string mazeGen::toString() {
    std::stringstream mazeOut;
    for (int i = 0; i < numCells; i++) {
        mazeOut << std::hex << Maze[i];
        if (i%N == N-1) {
            mazeOut << std::endl;
        }
    }
    return mazeOut.str();
}

void mazeGen::breakWall(int cellIndex, int wall) {
    if (wall == TOP) {
        Maze[cellIndex] = Maze[cellIndex] ^ TOP; 
        Maze[above(cellIndex)] = Maze[above(cellIndex)] ^ BOTTOM;
        MazeSets->nunion(cellIndex, above(cellIndex));
    } else if (wall == RIGHTSIDE) {
        Maze[cellIndex] = Maze[cellIndex] ^ RIGHTSIDE; 
        Maze[right(cellIndex)] = Maze[right(cellIndex)] ^ LEFTSIDE;
        MazeSets->nunion(cellIndex, right(cellIndex));
    } else if (wall == BOTTOM) {
        Maze[cellIndex] = Maze[cellIndex] ^ BOTTOM;
        Maze[below(cellIndex)] = Maze[below(cellIndex)] ^ TOP;
        MazeSets->nunion(cellIndex, below(cellIndex));
    } else if (wall == LEFTSIDE) {
        Maze[cellIndex] = Maze[cellIndex] ^ LEFTSIDE;
        Maze[left(cellIndex)] = Maze[left(cellIndex)] ^ RIGHTSIDE;
        MazeSets->nunion(cellIndex, left(cellIndex));
    }
}

// returns true if it's safe to break wall, otherwise returns false
bool mazeGen::checkBounds(int cellIndex, int wall) {
    int otherCell;
    if (wall == TOP) {
        otherCell = above(cellIndex);
    } else if (wall == RIGHTSIDE) {
        otherCell = right(cellIndex);
    } else if (wall == BOTTOM) {
        otherCell = below(cellIndex);
    } else if (wall == LEFTSIDE) {
        otherCell = left(cellIndex);
    }
    
    // if the wall makes up the boundaries of the maze then it cannot
    // be broken. The top,bottom,left,right helper function return -1
    // in this case
    if (otherCell == -1 || otherCell > numCells) return false;
    
    // if the cells are already in union don't break set
    if (MazeSets->sameComp(cellIndex, otherCell)) return false;
    
    return true;
}

void mazeGen::shuffle(std::vector<int> &indices) {
    int temp; int swaptarget;
    for (int i = indices.size() - 1; i >= 0; i--) {
        swaptarget = rand() % (i+1);
        temp = indices[i];
        indices[i] = indices[swaptarget];
        indices[swaptarget] = temp;
    }
}

int mazeGen::above(int x) {
    if (x-N < 0) return -1;
    return x - N;
}

int mazeGen::right(int x) {
    if (x%N == N-1) return -1;
    return x + 1;
}

int mazeGen::below(int x) {
    if (x+N > numCells-1) return -1;
    return x + N;
}

int mazeGen::left(int x) {
    if (x%N == 0) return -1;
    return x - 1;
}