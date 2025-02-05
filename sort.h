#ifndef SORT_H
#define SORT_H

#include "array.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

// Функция сравнения для сортировки
bool compareStudents(const StudentRecord& a, const StudentRecord& b) {
    if (a.group.value != b.group.value)
        return a.group.value < b.group.value; // По возрастанию номера группы
    return std::tie(a.name.surname, a.name.name, a.name.middlename) > 
           std::tie(b.name.surname, b.name.name, b.name.middlename); // По убыванию ФИО
}

// Сортировка вставками (устойчивая)
template <typename T>
void insertionSort(LibArray<T>& arr) {
    size_t n = arr.getSize();
    size_t processed = 0;
    for (size_t i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && compareStudents(key, arr[j])) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;

        // Логирование прогресса каждые 10000 элементов
        ++processed;
        if (processed % 10000 == 0) {
            std::cout << "Insertion Sort: Processed " << processed << " records...\n";
        }
    }
}

// Пирамидальная сортировка "на месте" без явного построения кучи
template <typename T>
void heapSort(LibArray<T>& arr) {
    size_t n = arr.getSize();
    size_t processed = 0;
    
    for (size_t i = 1; i < n; ++i) {
        size_t child = i;
        while (child > 0) {
            size_t parent = (child - 1) / 2;
            if (!compareStudents(arr[parent], arr[child])) {
                break;
            }
            std::swap(arr[parent], arr[child]);
            child = parent;
        }

        // Логируем прогресс
        ++processed;
        if (processed % 10000 == 0) {
            std::cout << "Heap Sort: Building heap, processed " << processed << " records...\n";
        }
    }
    
    // Упорядочиваем элементы, вытягивая корень в конец массива
    processed = 0;
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        
        size_t parent = 0;
        while (true) {
            size_t left = 2 * parent + 1;
            size_t right = 2 * parent + 2;
            size_t largest = parent;
            
            if (left < i && compareStudents(arr[largest], arr[left])) {
                largest = left;
            }
            if (right < i && compareStudents(arr[largest], arr[right])) {
                largest = right;
            }
            if (largest == parent) {
                break;
            }
            std::swap(arr[parent], arr[largest]);
            parent = largest;
        }

        // Логируем прогресс при каждом обмене
        ++processed;
        if (processed % 10000 == 0) {
            std::cout << "Heap Sort: Processed " << processed << " records...\n";
        }
    }
}

#endif
