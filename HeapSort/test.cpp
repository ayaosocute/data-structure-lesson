#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "HeapSort.h"

template<typename T>
bool check(const std::vector<T>& vec) {//这是一个检验排序正确性的函数
    for (size_t i = 1; i < vec.size(); i++) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> generateRandomVector(size_t size) {//随机生成一个序列
    std::vector<int> vec(size);
    for (auto& val : vec) {
        val = rand() % 1000000; 
    }
    return vec;
}

std::vector<int> generateSortedVector(size_t size) {//生成有序序列
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; i++) {
        vec[i] = i;
    }
    return vec;
}

std::vector<int> generateReverseSortedVector(size_t size) {//生成逆序序列
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; i++) {
        vec[i] = size - i;
    }
    return vec;
}

std::vector<int> generatePartiallyDuplicatedVector(size_t size) {//0-99重复的序列
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; i++) {
        vec[i] = i % 100;
    }
    std::random_shuffle(vec.begin(), vec.end());
    return vec;
}

template<typename T>
void testSorting(std::vector<T> vec, const std::string& description) {

    std::vector<T> vec1=vec;

    std::cout << "Testing " << description << "..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    heapSort(vec);
    auto end = std::chrono::high_resolution_clock::now();//记录堆排序开始与结束的时间
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time taken by heapSort: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "check: " << (check(vec) ? "Yes" : "No") << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(vec1.begin(), vec1.end());
    end = std::chrono::high_resolution_clock::now();//记录sort的时间
    elapsed = end - start;
    std::cout << "Time taken by std::sort_heap: " << elapsed.count() << " seconds" << std::endl;
}

int main() {
    const size_t size = 1000000;
    srand(time(nullptr));

    testSorting(generateRandomVector(size), "random sequence");//测试4种情况
    testSorting(generateSortedVector(size), "sorted sequence");
    testSorting(generateReverseSortedVector(size), "reverse sorted sequence");
    testSorting(generatePartiallyDuplicatedVector(size), "partially duplicated sequence");

    return 0;
}