#pragma once
#ifndef EDGE_H
#define EDGE_H

struct Edge {
    int destination;
    int weight;

    Edge() : destination(-1), weight(0) {}
    Edge(int dest, int w) : destination(dest), weight(w) {}
};

#endif