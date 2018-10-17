/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Feargus
 *
 * Make and solve an nxn dimension maze
 * where n is user inputted.
 */

#include "mazeGen.h"
#include "mazeSolve.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    
    cout << "Enter maze dimension: ";
    int mazeDim;
    cin >> mazeDim;

    if (mazeDim < 3) {
        cerr << "Value must be 3 or greater" << endl;
        exit(1);
    }
    
    mazeGen myMaze(mazeDim);
    myMaze.generateMaze();

    string mazeOut = myMaze.printMaze();
    cout << mazeOut;
    
    mazeSolve solution(mazeOut);
    solution.solve(); 
    
    return 0;
}

