#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <climits>
#include <algorithm>

struct Vertex {
    int id;
    int distance;

    Vertex() : id(-1), distance(INT_MAX) {}
    Vertex(int id, int distance) : id(id), distance(distance) {}

    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }

    bool operator<(const Vertex& other) const {
        return distance < other.distance;
    }

    bool operator==(const Vertex& other) const {
        return id == other.id;
    }

    bool operator<=(const Vertex& other) const {
        return distance <= other.distance;
    }

    bool operator>=(const Vertex& other) const {
        return distance >= other.distance;
    }
};

#endif