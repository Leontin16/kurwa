#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <climits>
#include <algorithm>  // Для std::min

struct Vertex {
    int id;
    int distance;

    Vertex() : id(-1), distance(INT_MAX) {}
    Vertex(int id, int distance) : id(id), distance(distance) {}

    // Критическое исправление: сравниваем ТОЛЬКО по расстоянию
    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }

    bool operator<(const Vertex& other) const {
        return distance < other.distance;
    }

    // Для устранения дубликатов в куче
    bool operator==(const Vertex& other) const {
        return id == other.id;  // Сравниваем по id!
    }

    bool operator<=(const Vertex& other) const {
        return distance <= other.distance;
    }

    bool operator>=(const Vertex& other) const {
        return distance >= other.distance;
    }
};

#endif