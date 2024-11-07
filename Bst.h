#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>

// Templated Node class
template <class T>
class Node
{
public:
    T data;
    Node* left;
    Node* right;

    // Constructor with body initialization (not using initializer list)
    Node(T value)
    {
        data = value;    // Initialize data
        left = nullptr;  // Initialize left pointer
        right = nullptr; // Initialize right pointer
    }
};

// Templated Bst class
template <class T>
class Bst
{
private:
    Node<T>* root;

    // Helper functions
    Node<T>* insertRecursive(Node<T>* node, T value);
    Node<T>* deleteRecursive(Node<T>* node, T value);
    Node<T>* searchRecursive(Node<T>* node, T value);
    void inOrderRecursive(Node<T>* node, void (*func)(T)) const;
    void preOrderRecursive(Node<T>* node, void (*func)(T)) const;
    void postOrderRecursive(Node<T>* node, void (*func)(T)) const;
    Node<T>* findMin(Node<T>* node);
    void deleteTree(Node<T>* node);
    Node<T>* copyTree(Node<T>* node);

public:
    Bst();       // Constructor
    ~Bst();      // Destructor

    Bst(const Bst<T>& other);               // Copy constructor
    Bst<T>& operator=(const Bst<T>& other);  // Assignment operator

    void insert(T value);
    void remove(T value);
    bool search(T value);
    void inOrder(void (*func)(T)) const;  // Accept a function pointer for in-order traversal
    void preOrder(void (*func)(T)) const;  // Accept a function pointer for pre-order traversal
    void postOrder(void (*func)(T)) const;  // Accept a function pointer for post-order traversal
};

// Constructor
template <class T>
Bst<T>::Bst()
{
    root = nullptr;  // Initialize root pointer to nullptr
}

// Destructor
template <class T>
Bst<T>::~Bst()
{
    deleteTree(root);  // Delete the entire tree
}

// Copy Constructor (Deep copy)
template <class T>
Bst<T>::Bst(const Bst<T>& other)
{
    if (this != &other) {
        root = copyTree(other.root); // Deep copy the tree
    } else {
        root = nullptr;
    }
}

// Assignment Operator (Deep copy)
template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other) {
        deleteTree(root);  // Delete current tree
        root = copyTree(other.root);  // Deep copy the tree
    }
    return *this;
}

// Insert a value into the tree
template <class T>
void Bst<T>::insert(T value)
{
    root = insertRecursive(root, value);  // Call recursive insert
}

// Recursive insert helper function
template <class T>
Node<T>* Bst<T>::insertRecursive(Node<T>* node, T value)
{
    if (node == nullptr) {
        return new Node<T>(value);  // Create new node if reached empty spot
    }

    if (value < node->data) {
        node->left = insertRecursive(node->left, value);  // Go left if value is smaller
    } else {
        node->right = insertRecursive(node->right, value);  // Go right if value is larger or equal
    }
    return node;  // Return the node (modified or unchanged)
}

// Remove a value from the tree
template <class T>
void Bst<T>::remove(T value)
{
    root = deleteRecursive(root, value);  // Call recursive delete
}

// Recursive remove helper function
template <class T>
Node<T>* Bst<T>::deleteRecursive(Node<T>* node, T value)
{
    if (node == nullptr) {
        return nullptr;  // Value not found
    }

    if (value < node->data) {
        node->left = deleteRecursive(node->left, value);  // Go left
    } else if (value > node->data) {
        node->right = deleteRecursive(node->right, value);  // Go right
    } else {
        // Node to be deleted found
        if (node->left == nullptr) {
            Node<T>* temp = node->right;
            delete node;
            return temp;  // Replace with right child
        } else if (node->right == nullptr) {
            Node<T>* temp = node->left;
            delete node;
            return temp;  // Replace with left child
        } else {
            Node<T>* temp = findMin(node->right);  // Find in-order successor
            node->data = temp->data;
            node->right = deleteRecursive(node->right, temp->data);  // Delete the successor
        }
    }
    return node;
}

// Search for a value in the tree
template <class T>
bool Bst<T>::search(T value)
{
    return searchRecursive(root, value);
}

// Recursive search helper function
template <class T>
Node<T>* Bst<T>::searchRecursive(Node<T>* node, T value)
{
    if (node == nullptr) {
        return nullptr;
    }
    if (node->data == value) {
        return node;  // Found the node
    }
    if (value < node->data) {
        return searchRecursive(node->left, value);  // Search left
    } else {
        return searchRecursive(node->right, value);  // Search right
    }
}

// In-order traversal using function pointer
template <class T>
void Bst<T>::inOrder(void (*func)(T)) const
{
    inOrderRecursive(root, func);  // Call the recursive in-order function
}

// Recursive in-order helper function
template <class T>
void Bst<T>::inOrderRecursive(Node<T>* node, void (*func)(T)) const
{
    if (node != nullptr) {
        inOrderRecursive(node->left, func);  // Visit left subtree
        func(node->data);                    // Apply function to node data
        inOrderRecursive(node->right, func); // Visit right subtree
    }
}

// Pre-order traversal using function pointer
template <class T>
void Bst<T>::preOrder(void (*func)(T)) const
{
    preOrderRecursive(root, func);  // Call the recursive pre-order function
}

// Recursive pre-order helper function
template <class T>
void Bst<T>::preOrderRecursive(Node<T>* node, void (*func)(T)) const
{
    if (node != nullptr) {
        func(node->data);                    // Apply function to node data
        preOrderRecursive(node->left, func);  // Visit left subtree
        preOrderRecursive(node->right, func); // Visit right subtree
    }
}

// Post-order traversal using function pointer
template <class T>
void Bst<T>::postOrder(void (*func)(T)) const
{
    postOrderRecursive(root, func);  // Call the recursive post-order function
}

// Recursive post-order helper function
template <class T>
void Bst<T>::postOrderRecursive(Node<T>* node, void (*func)(T)) const
{
    if (node != nullptr) {
        postOrderRecursive(node->left, func);  // Visit left subtree
        postOrderRecursive(node->right, func); // Visit right subtree
        func(node->data);                      // Apply function to node data
    }
}

// Find the minimum node (for removing a node with two children)
template <class T>
Node<T>* Bst<T>::findMin(Node<T>* node)
{
    while (node && node->left != nullptr)
        node = node->left;  // Move to the leftmost node
    return node;  // Return the minimum node
}

// Delete the entire tree recursively
template <class T>
void Bst<T>::deleteTree(Node<T>* node)
{
    if (node != nullptr) {
        deleteTree(node->left);   // Delete left subtree
        deleteTree(node->right);  // Delete right subtree
        delete node;              // Delete current node
    }
}

// Copy tree recursively (used in copy constructor and assignment operator)
template <class T>
Node<T>* Bst<T>::copyTree(Node<T>* node)
{
    if (node == nullptr) {
        return nullptr;
    }
    Node<T>* newNode = new Node<T>(node->data);  // Create new node
    newNode->left = copyTree(node->left);        // Copy left subtree
    newNode->right = copyTree(node->right);      // Copy right subtree
    return newNode;                              // Return new node
}

#endif // BST_H_INCLUDED
