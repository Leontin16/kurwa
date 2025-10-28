#pragma once
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "min_heap.h"
#include "vector.h"
#include <climits>
#include <algorithm>

class Dijkstra {
public:
    static Vector<int> findShortestPaths(const Graph& graph, int source) {
        int n = graph.getNumVertices();
        Vector<int> distances(n);
        MinHeap minHeap(n);

        for (int i = 0; i < n; i++) {
            distances[i] = INT_MAX;
        }
        distances[source] = 0;

        for (int i = 0; i < n; i++) {
            minHeap.push(Vertex(i, distances[i]));
        }

        int processed = 0;
        while (!minHeap.isEmpty()) {
            Vertex current = minHeap.pop();
            int u = current.id;

            if (distances[u] == INT_MAX) {
                break;
            }

            const Vector<Edge>& neighbors = graph.getNeighbors(u);
            for (int i = 0; i < neighbors.size(); i++) {
                const Edge& edge = neighbors[i];
                int v = edge.destination;
                int weight = edge.weight;

                if (distances[u] < INT_MAX - weight) {
                    int newDistance = distances[u] + weight;

                    if (newDistance < distances[v]) {
                        distances[v] = newDistance;
                        minHeap.decreaseKey(v, newDistance);
                    }
                }
            }

            processed++;
            if (processed >= n) break;
        }

        return distances;
    }
};

#endif