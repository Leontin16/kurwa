#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <climits>

template <typename T>
class Vector {
private:
    T* data;
    int capacity_;
    int size_;

public:
    Vector() : data(nullptr), capacity_(0), size_(0) {}

    explicit Vector(int initialCapacity) : capacity_(initialCapacity), size_(initialCapacity) {
        if (initialCapacity > 0) {
            data = new T[initialCapacity];
            for (int i = 0; i < initialCapacity; i++) {
                data[i] = T();
            }
        }
        else {
            data = nullptr;
        }
    }

    Vector(const Vector& other) : capacity_(other.capacity_), size_(other.size_) {
        if (capacity_ > 0) {
            data = new T[capacity_];
            for (int i = 0; i < size_; i++) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;

            capacity_ = other.capacity_;
            size_ = other.size_;

            if (capacity_ > 0) {
                data = new T[capacity_];
                for (int i = 0; i < size_; i++) {
                    data[i] = other.data[i];
                }
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            int new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }
        data[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        size_ = 0;
    }

    void reserve(int new_capacity) {
        if (new_capacity <= capacity_) return;

        T* new_data = new T[new_capacity];

        for (int i = 0; i < size_; i++) {
            new_data[i] = data[i];
        }

        for (int i = size_; i < new_capacity; i++) {
            new_data[i] = T();
        }

        delete[] data;
        data = new_data;
        capacity_ = new_capacity;
    }

    int getCapacity() const {
        return capacity_;
    }

    
    T* begin() { return data; }
    T* end() { return data + size_; }
    const T* begin() const { return data; }
    const T* end() const { return data + size_; }
};

#endif // VECTOR_H