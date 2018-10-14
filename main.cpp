/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Feargus
 *
 * Created on October 13, 2018, 5:40 PM
 */

#include "disjointSet.h"
#include "mazeGen.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    
    cout << "Enter maze dimension: ";
    int mazeDim;
    cin >> mazeDim;

    //int mazeDim = atoi(argv[1]);
    if (mazeDim < 3) {
        cerr << "Value must be 3 or greater" << endl;
        exit(1);
    }
    
    mazeGen myMaze(mazeDim);
    myMaze.generateMaze();
    
    string mazeOut = myMaze.printMaze();
    cout << mazeOut;
    
    return 0;
}

