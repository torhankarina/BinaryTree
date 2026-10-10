#ifndef H_BTREE
#define H_BTREE

#include "node.h"
#include <cstdlib>

// enumeration for random subtree selection
typedef enum { left_side, right_side } SIDE;

// random side selector
inline SIDE rnd() {
    return std::rand() % 2 ? right_side : left_side;
}

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

// default constructor
template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

// public getSize
template <typename T>
unsigned BinaryTree<T>::getSize() const {
    return _getSize(root);
}

// private getSize
template <typename T>
unsigned BinaryTree<T>::_getSize(Node<T> *node) const {
    if (node == nullptr)
        return 0;
    return 1 + _getSize(node->left) + _getSize(node->right);
}

// public getHeight
template <typename T>
unsigned BinaryTree<T>::getHeight() const {
    return _getHeight(root);
}

// private getHeight (note: root-only tree height is 1 per refout)
template <typename T>
unsigned BinaryTree<T>::_getHeight(Node<T> *node) const {
    if (node == nullptr)
        return 0;
    unsigned left_h = _getHeight(node->left);
    unsigned right_h = _getHeight(node->right);
    return 1 + (left_h > right_h ? left_h : right_h);
}

// public Insert
template <typename T>
void BinaryTree<T>::Insert(const T &x) {
    _Insert(root, x);
}

// private Insert
template <typename T>
void BinaryTree<T>::_Insert(Node<T> *&node, const T &x) {
    if (node == nullptr) {
        node = new Node<T>(x);
    } else {
        if (rnd() == left_side)
            _Insert(node->left, x);
        else
            _Insert(node->right, x);
    }
}

// public Inorder
template <typename T>
void BinaryTree<T>::Inorder(void (*visit)(const T&)) {
    _Inorder(root, visit);
}

// private Inorder
template <typename T>
void BinaryTree<T>::_Inorder(Node<T> *node, void (*visit)(const T&)) {
    if (node != nullptr) {
        _Inorder(node->left, visit);
        visit(node->data);
        _Inorder(node->right, visit);
    }
}

#endif // End of H_BTREE