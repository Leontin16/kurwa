#pragma once
#ifndef EDGE_H
#define EDGE_H

struct Edge {
    int destination;    //вершина
    int weight;         //вес

    Edge() : destination(-1), weight(0) {}
    Edge(int dest, int w) : destination(dest), weight(w) {}
};

#endif