/* 
 * File:   mazeGen.h
 * Author: Feargus
 *
 * Generates a square maze using disjoint sets.
 * 
 * TODO: enumerate TOP, BOTTOM, LEFT, RIGHT
 */

#include "disjointSet.h"
#include "mazeGen.h"
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
    delete[] MazeSets; MazeSets = 0;
}

// TODO: the biggest thing to do is clean up
// and modularize this function
void mazeGen::generateMaze() {
    std::vector<int> copy = indices;
    // TODO: write shuffle algorithm to shuffle indices
    shuffle(indices);
    
    int numUnions = 0;              // TODO: VVV can below be done with an array and index?
    int index = indices.size() - 1; // start at back to easily pop
    while (numUnions < numCells - 1) { // when numUnions = numCells - 1 everything is in union
        if (index == 0) { // if we've been through all the indices and not everything is in union
            indices = copy; // then restart 
            index = indices.size() - 1;
        } // TODO: can this be put at the end of the loop?
        
        // random cell to work with from randomly shuffled vector of all indices
        int cellIndex = indices[index]; // rename to randIndex?
        
        int wallToBreak = rand()%4; // randomly select a wall to break
        bool canBreakWall = checkBounds(cellIndex, wallToBreak);
        int tryWall = wallToBreak;
        bool doBreakWall = true; // used to make sure we don't increase numUnions 
                                // when a cell is in union with all its neighbors
        
        while (!canBreakWall) {
            tryWall = (1 + tryWall) % 4; // increment through other walls
            canBreakWall = checkBounds(cellIndex, tryWall);
            
            if (tryWall == wallToBreak) { // this means we've come back to original tryWall
                        // so it's in union with it's neighbors and we don't need to do anything with it
                indices.pop_back();
                index--;
                canBreakWall = true;
                doBreakWall = false;
            }
            
            if (canBreakWall) wallToBreak = tryWall;
        }
        
        // TODO: This can definitely be modularized
        if (canBreakWall && doBreakWall) {
            breakWall(cellIndex, wallToBreak);
            // also need to break wall in adjacent cell
            if (wallToBreak == 0) { // top wall
                breakWall(top(cellIndex), 2); // 2 because break bottom
                MazeSets->nunion(cellIndex, top(cellIndex));
                numUnions++;
            } else if (wallToBreak == 1) { // right wall
                breakWall(right(cellIndex), 3); // 3 break left
                MazeSets->nunion(cellIndex, right(cellIndex));
                numUnions++;
            } else if (wallToBreak == 2) { // bottom wall
                breakWall(bottom(cellIndex), 0); // 0 break top
                MazeSets->nunion(cellIndex, bottom(cellIndex));
                numUnions++;
            } else if (wallToBreak == 3) { // left wall
                breakWall(left(cellIndex), 1); // 1 break right
                MazeSets->nunion(cellIndex, left(cellIndex));
                numUnions++;
            }
            index--;
        }  
    }
}

// rename toString?
std::string mazeGen::printMaze() {
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
    // 0 - top, 1 - right, 2 - bottom, 3 - left
    if (wall == 0) {                            // VVV can it binary xor?
        Maze[cellIndex] = Maze[cellIndex] - 8; // the difference in hex value for cell type when removing top
    } else if (wall == 1) {
        Maze[cellIndex] = Maze[cellIndex] - 1; // and so on
    } else if (wall == 2) {
        Maze[cellIndex] = Maze[cellIndex] - 2;
    } else if (wall == 3) {
        Maze[cellIndex] = Maze[cellIndex] - 4;
    }
}

// returns true if it's safe to break wall, otherwise returns false
bool mazeGen::checkBounds(int cellIndex, int wall) {
    // 0 - top, 1 - right, 2 - bottom, 3 - left
    int otherCell;
    if (wall == 0) {
        otherCell = top(cellIndex);
    } else if (wall == 1) {
        otherCell = right(cellIndex);
    } else if (wall == 2) {
        otherCell = bottom(cellIndex);
    } else if (wall == 3) {
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

int mazeGen::top(int x) {
    if (x-N < 0) return -1;
    return x - N;
}

int mazeGen::right(int x) {
    if (x%N == N-1) return -1;
    return x + 1;
}

int mazeGen::bottom(int x) {
    if (x+N > numCells-1) return -1;
    return x + N;
}

int mazeGen::left(int x) {
    if (x%N == 0) return -1;
    return x - 1;
}