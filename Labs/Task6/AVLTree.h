#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>

// Node struct template
template <typename T>
struct Node {
    T val;
    Node* left;
    Node* right;
    int height;

    Node(T value) : val(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    Node<T>* root;

    // Utility functions
    int getHeight(Node<T>* node);
    int balanceFactor(Node<T>* node);
    void updateHeight(Node<T>* node);

    // Rotations
    Node<T>* rotateRight(Node<T>* y);
    Node<T>* rotateLeft(Node<T>* x);

    // Balancing
    Node<T>* balance(Node<T>* node);

    // Core operations
    Node<T>* insert(Node<T>* node, T val);
    Node<T>* remove(Node<T>* node, T val);
    Node<T>* minValueNode(Node<T>* node);

    // Traversal and cleanup
    void inOrder(Node<T>* node);
    void clear(Node<T>* node);

public:
    AVLTree();
    ~AVLTree();

    void insertNode(T val);
    void deleteNode(T val);
    void printInOrder();
};

#include "AVLTree.cpp" // include implementation (template requirement)

#endif // AVLTREE_H
