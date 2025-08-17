#include "AVLTree.h"

int main() {
    AVLTree<int> tree;

    tree.insertNode(30);
    tree.insertNode(20);
    tree.insertNode(40);
    tree.insertNode(10);
    tree.insertNode(25);
    tree.insertNode(50);
    tree.insertNode(5);

    std::cout << "In-order traversal of AVL Tree: ";
    tree.printInOrder();

    tree.deleteNode(20);
    std::cout << "After deleting 20: ";
    tree.printInOrder();

    return 0;
}
