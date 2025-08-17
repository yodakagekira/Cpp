#include "AVLTree.h"

// Constructor & Destructor
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree() {
    clear(root);
}

// Utility functions
template <typename T>
int AVLTree<T>::getHeight(Node<T>* node) {
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::balanceFactor(Node<T>* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename T>
void AVLTree<T>::updateHeight(Node<T>* node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

// Rotations
template <typename T>
Node<T>* AVLTree<T>::rotateRight(Node<T>* y) {
    Node<T>* x = y->left;
    Node<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

template <typename T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* x) {
    Node<T>* y = x->right;
    Node<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balance a node
template <typename T>
Node<T>* AVLTree<T>::balance(Node<T>* node) {
    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Insert node
template <typename T>
Node<T>* AVLTree<T>::insert(Node<T>* node, T val) {
    if (!node) return new Node<T>(val);

    if (val < node->val)
        node->left = insert(node->left, val);
    else if (val > node->val)
        node->right = insert(node->right, val);
    else
        return node; // No duplicates

    return balance(node);
}

// Find minimum value node
template <typename T>
Node<T>* AVLTree<T>::minValueNode(Node<T>* node) {
    Node<T>* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Remove node
template <typename T>
Node<T>* AVLTree<T>::remove(Node<T>* node, T val) {
    if (!node) return nullptr;

    if (val < node->val) {
        node->left = remove(node->left, val);
    } 
    else if (val > node->val) {
        node->right = remove(node->right, val);
    } 
    else {
        // Case 1 & 2: node has at most one child
        if (!node->left || !node->right) {
            Node<T>* child = node->left ? node->left : node->right;
            delete node;
            return child; 
        }

        // Case 3: node has two children
        Node<T>* successor = minValueNode(node->right);
        node->val = successor->val;
        node->right = remove(node->right, successor->val);
    }

    return balance(node);
}


// Traversal
template <typename T>
void AVLTree<T>::inOrder(Node<T>* node) {
    if (!node) return;
    inOrder(node->left);
    std::cout << node->val << " ";
    inOrder(node->right);
}

// Clear memory
template <typename T>
void AVLTree<T>::clear(Node<T>* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Public methods
template <typename T>
void AVLTree<T>::insertNode(T val) {
    root = insert(root, val);
}

template <typename T>
void AVLTree<T>::deleteNode(T val) {
    root = remove(root, val);
}

template <typename T>
void AVLTree<T>::printInOrder() {
    inOrder(root);
    std::cout << std::endl;
}
