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
        std::cout << "Graph: создание графа с " << vertices << " вершинами" << std::endl;

        // —оздаем пустой вектор
        adjacencyList = Vector<Vector<Edge>>();

        // «атем добавл€ем пустые вектора дл€ каждой вершины
        for (int i = 0; i < vertices; i++) {
            Vector<Edge> emptyList;
            adjacencyList.push_back(emptyList);
            std::cout << "Graph: добавлена вершина " << i + 1 << std::endl;
        }

        std::cout << "Graph: инициализаци€ завершена, размер adjacencyList: " << adjacencyList.size() << std::endl;
    }

    void addEdge(int source, int destination, int weight) {
        
        if (source < 0 || source >= numVertices) {
            std::cout << "ќшибка: исходна€ вершина " << source + 1 << " вне диапазона" << std::endl;
            return;
        }
        if (destination < 0 || destination >= numVertices) {
            std::cout << "ќшибка: конечна€ вершина " << destination + 1 << " вне диапазона" << std::endl;
            return;
        }

        std::cout << "Graph: добавление ребра " << source + 1 << " -> " << destination + 1 << " вес " << weight << std::endl;
        adjacencyList[source].push_back(Edge(destination, weight));
        std::cout << "Graph: ребро добавлено успешно" << std::endl;
    }

    const Vector<Edge>& getNeighbors(int vertex) const {
        if (vertex < 0 || vertex >= numVertices) {
            throw std::out_of_range("Graph vertex index out of range");
        }
        return adjacencyList[vertex];
    }

    int getNumVertices() const {
        return numVertices;
    }
};

#endif