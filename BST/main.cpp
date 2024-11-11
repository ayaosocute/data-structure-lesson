#include <iostream>
#include "BST.h"  // 假设 BinarySearchTree 类定义在这个头文件中

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    // 测试插入功能
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    bst.insert(1);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);   
    // 测试打印树结构
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试删除功能
    bst.remove(8);//叶子节点
    std::cout << "Tree after removing 8:" << std::endl;
    bst.printTree();

    bst.remove(5);//左右儿子都有的节点
    std::cout << "Tree after removing 5:" << std::endl;
    bst.printTree();

    bst.remove(7);//只有左儿子的节点
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();

    bst.remove(12);
    bst.remove(15);//只有右儿子的节点
    std::cout << "Tree after removing 12 and 15:" << std::endl;
    bst.printTree();   
    // 测试清空树
    bst.makeEmpty();
    std::cout << "Tree after making empty:" << std::endl;
    bst.printTree();

}

int main() {
    testBinarySearchTree();
    return 0;
}