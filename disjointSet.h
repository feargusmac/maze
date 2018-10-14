/* 
 * File:   disjointSet.h
 * Author: Feargus
 *
 * Union-Find data structure. Tracks a set
 * of elements partitioned into a number
 * of non-overlapping subsets.
 */

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class disjointSet{
    
public:
    disjointSet();
    disjointSet(int);
    ~disjointSet();
    void makeSet(int);
    void nunion(int, int); // union is already a key word, so nunion for new union I guess
    void link(int, int);
    int findSet(int);
    bool sameComp(int, int);
    
private:
    int *parent;
    int *rank;
    
};


#endif /* DISJOINTSET_H */

