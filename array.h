#ifndef LIB_ARRAY_H
#define LIB_ARRAY_H

#include <stdexcept>
// Страшно
template <typename T>
class LibArray {
private:
    T* data;
    size_t size;

public:

    LibArray(size_t size) : size(size) {
        if (size == 0) throw std::invalid_argument("Size cannot be zero");
        data = new T[size];
    }


    ~LibArray() { delete[] data; }

    LibArray(LibArray&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }


    LibArray& operator=(LibArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    LibArray(const LibArray& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
    }


    LibArray& operator=(const LibArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t getSize() const { return size; }

    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }
};

#endif