/* 
 * File:   disjointSet.cpp
 * Author: Feargus
 *
 * Union-Find data structure. Tracks a set
 * of elements partitioned into a number
 * of non-overlapping subsets.
 * See disjointSet.h
 */

#include "disjointSet.h"

disjointSet::disjointSet() {
}

disjointSet::disjointSet(int n) {
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; i++) {
        makeSet(i);
    }
}

disjointSet::~disjointSet() {
    delete[] parent; parent = 0;
    delete[] rank; rank = 0;
}

void disjointSet::makeSet(int x) {
    parent[x] = x;
    rank[x] = 0;
}

void disjointSet::nunion(int x, int y) {
    link(findSet(x), findSet(y));
}

void disjointSet::link(int x, int y) {
    if (x == y) return;
    if (rank[x] > rank[y]) {
        parent[y] = x;
    } else {
        parent[x] = y;
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

int disjointSet::findSet(int x) {
    if (x != parent[x]) {
        parent[x] = findSet(parent[x]);
    }
    return parent[x];
}

bool disjointSet::sameComp(int x, int y) {
    return (findSet(x) == findSet(y));
}