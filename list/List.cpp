#include "List.h"
#include <iostream>

int main() {  
    // 测试默认构造函数和 push_back  
    List<int> list;  
    list.push_back(10);  
    list.push_back(20);  
    list.push_back(30);  
    std::cout << "After push_back: ";  
    for (auto x : list) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试拷贝构造函数  
    List<int> list2(list);  
    std::cout << "After copy constructor: ";  
    for (auto x : list2) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试移动构造函数  
    List<int> list3(std::move(list2));  
    std::cout << "After move constructor: ";  
    for (auto x : list3) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试赋值运算符  
    List<int> list4;  
    list4 = list3;  
    std::cout << "After assignment operator: ";  
    for (auto x : list4) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试移动赋值运算符  
    List<int> list5;  
    list5 = std::move(list4);  
    std::cout << "After move assignment operator: ";  
    for (auto x : list5) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试初始化列表构造函数  
    List<int> list6 = {1, 2, 3, 4, 5};  
    std::cout << "After initializer list constructor: ";  
    for (auto x : list6) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试 front, back  
    std::cout << "Front element: " << list6.front() << std::endl;  
    std::cout << "Back element: " << list6.back() << std::endl;  
  
    // 测试 push_front, pop_front, pop_back  
    list6.push_front(0);  
    list6.pop_front();  
    list6.pop_back();  
    std::cout << "After push_front, pop_front, pop_back: ";  
    for (auto x : list6) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试 insert  
    auto it = list6.begin();  
    ++it;  
    list6.insert(it, 99);  
    std::cout << "After insert: ";  
    for (auto x : list6) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试 erase  
    it = list6.begin();  
    list6.erase(it);  
    std::cout << "After erase: ";  
    for (auto x : list6) std::cout << x << " ";  
    std::cout << std::endl;  
  
    // 测试 clear  
    list6.clear();  
    std::cout << "After clear, size: " << list6.size() << std::endl;  
  
    // 测试迭代器的 ++ 和 -- 操作  
    list.push_back(1);  
    list.push_back(2);  
    list.push_back(3);  
    auto iter = list.begin();  
    std::cout << "Testing iterator increment: ";  
    for (; iter != list.end(); ++iter) {  
        std::cout << *iter << " ";  
    }  
    std::cout << std::endl;  
  
    std::cout << "Testing iterator decrement: ";  
    for (--iter; iter != list.begin(); --iter) {  
        std::cout << *iter << " ";  
    }  
    std::cout << *iter << std::endl;  
  
    return 0;  
}