#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>

template<typename T>
void heapSort(std::vector<T>& vec) {
    std::make_heap(vec.begin(), vec.end());//我们先将其转换为最大堆
    for (auto it = vec.end(); it != vec.begin(); --it) {
        std::pop_heap(vec.begin(), it);//每一次都将最大元素移动到向量的末尾，并调整剩余部分保持堆的性质，从而达到排序的目的
    }
}

#endif // HEAPSORT_H