#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include "edge.h"
#include <iostream>

class Graph {
private:
    int numVertices;
    Vector<Vector<Edge>> adjacencyList;

public:
    Graph(int vertices) : numVertices(vertices) {
        adjacencyList = Vector<Vector<Edge>>();
        for (int i = 0; i < vertices; i++) {
            Vector<Edge> emptyList;
            adjacencyList.push_back(emptyList);
        }
    }

    void addEdge(int source, int destination, int weight) {
        if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) {
            return;
        }
        adjacencyList[source].push_back(Edge(destination, weight));
    }

    const Vector<Edge>& getNeighbors(int vertex) const {
        return adjacencyList[vertex];
    }

    int getNumVertices() const {
        return numVertices;
    }

    void clear() {
        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i].clear();
        }
    }
};

#endif