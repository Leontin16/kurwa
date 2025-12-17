#pragma once
#ifndef MINHEAP_H
#define MINHEAP_H

#include "vector.h"
#include "vertex.h"

class MinHeap {
private:
    static const int D = 15;
    Vector<Vertex> heap;
    Vector<int> vertexPositions;

    int parent(int index) const {
        return (index - 1) / D;
    }

    int firstChild(int index) const {
        return D * index + 1;
    }

    int lastChild(int index) const {
        return std::min(D * index + D, heap.size() - 1);
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = parent(index);
            if (heap[index] < heap[parentIndex]) {
                Vertex temp = heap[index];
                heap[index] = heap[parentIndex];
                heap[parentIndex] = temp;

                vertexPositions[heap[index].id] = index;
                vertexPositions[heap[parentIndex].id] = parentIndex;

                index = parentIndex;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (firstChild(index) < size) {
            int smallest = index;
            int firstChildIndex = firstChild(index);
            int lastChildIndex = lastChild(index);

            for (int i = firstChildIndex; i <= lastChildIndex; i++) {
                if (i < size && heap[i] < heap[smallest]) {
                    smallest = i;
                }
            }

            if (smallest != index) {
                Vertex temp = heap[index];
                heap[index] = heap[smallest];
                heap[smallest] = temp;

                vertexPositions[heap[index].id] = index;
                vertexPositions[heap[smallest].id] = smallest;

                index = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    MinHeap(int capacity) {
        heap = Vector<Vertex>();
        vertexPositions = Vector<int>();
        for (int i = 0; i < capacity; i++) {
            vertexPositions.push_back(-1);
        }
    }

    void push(const Vertex& vertex) {
        heap.push_back(vertex);
        int index = heap.size() - 1;
        vertexPositions[vertex.id] = index;
        heapifyUp(index);
    }

    Vertex pop() {
        if (heap.empty()) {
            return Vertex();
        }

        Vertex minVertex = heap[0];
        vertexPositions[minVertex.id] = -1;

        if (heap.size() > 1) {
            heap[0] = heap[heap.size() - 1];
            vertexPositions[heap[0].id] = 0;
        }
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }

        return minVertex;
    }

    void decreaseKey(int vertexId, int newDistance) {
        int index = vertexPositions[vertexId];
        if (index == -1 || heap[index].distance <= newDistance) {
            return;
        }

        heap[index].distance = newDistance;
        heapifyUp(index);
    }

    bool isEmpty() const {
        return heap.empty();
    }

    bool contains(int vertexId) const {
        return vertexId < vertexPositions.size() && vertexPositions[vertexId] != -1;
    }

    int size() const {
        return heap.size();
    }

    bool isValid() const {
        for (int i = 1; i < heap.size(); i++) {
            int parentIndex = parent(i);
            if (heap[parentIndex] > heap[i]) {
                return false;
            }
        }
        return true;
    }
};

#endif