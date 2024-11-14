#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>

/**
 * @class Node
 * @brief Templated node class for Binary Search Tree
 *
 * This class represents a node in a Binary Search Tree. It stores the data and
 * has pointers to its left and right children. It is used as the building block
 * for the `Bst` class.
 *
 * @tparam T Type of data stored in the node (e.g., int, float).
 */
template <class T>
class Node
{
public:
    T data;        ///< Data stored in the node
    Node* left;    ///< Pointer to the left child node
    Node* right;   ///< Pointer to the right child node

    /**
     * @brief Constructor for Node class
     *
     * Initializes a node with the given value and sets both left and right pointers to nullptr.
     *
     * @param value The data to store in the node.
     */
    Node(T value)
    {
        data = value;    ///< Initialize data
        left = nullptr;  ///< Initialize left pointer
        right = nullptr; ///< Initialize right pointer
    }
};

/**
 * @class Bst
 * @brief Templated Binary Search Tree (BST) class
 *
 * This class implements a Binary Search Tree, which supports common operations such as insertion,
 * deletion, searching, and various tree traversals. It uses recursion for most of its operations.
 *
 * @tparam T The type of the data stored in the tree nodes (e.g., int, float).
 */
template <class T>
class Bst
{
private:
    Node<T>* root;  ///< Root node of the tree

    // Helper functions for recursive tree operations
    Node<T>* insertRecursive(Node<T>* node, T value);
    Node<T>* deleteRecursive(Node<T>* node, T value);
    Node<T>* searchRecursive(Node<T>* node, T value);
    int countNodesRecursive(Node<T>* node) const;
    T sumNodesRecursive(Node<T>* node) const;
    void inOrderRecursive(Node<T>* node, void (*func)(T)) const;
    void preOrderRecursive(Node<T>* node, void (*func)(T)) const;
    void postOrderRecursive(Node<T>* node, void (*func)(T)) const;
    Node<T>* findMin(Node<T>* node);
    void deleteTree(Node<T>* node);
    Node<T>* copyTree(Node<T>* node);

public:
    Bst();       ///< Constructor for Bst
    ~Bst();      ///< Destructor for Bst

    Bst(const Bst<T>& other);               ///< Copy constructor
    Bst<T>& operator=(const Bst<T>& other);  ///< Assignment operator

    void insert(T value);                  ///< Insert a value into the tree
    void remove(T value);                  ///< Remove a value from the tree
    bool search(T value);                  ///< Search for a value in the tree
    int count() const;                     ///< Return the number of nodes in the tree
    T sum() const;                         ///< Return the sum of all node values
    Node<T>* getRoot() const;              ///< Get the root node

    void inOrder(void (*func)(T)) const;   ///< In-order tree traversal with function pointer
    void preOrder(void (*func)(T)) const;  ///< Pre-order tree traversal with function pointer
    void postOrder(void (*func)(T)) const; ///< Post-order tree traversal with function pointer
};

/**
 * @brief Constructor for the Bst class
 *
 * Initializes the BST with a null root.
 */
template <class T>
Bst<T>::Bst()
{
    root = nullptr;  ///< Initialize root pointer to nullptr
}

/**
 * @brief Destructor for the Bst class
 *
 * Deletes the entire tree by calling the `deleteTree` helper function.
 */
template <class T>
Bst<T>::~Bst()
{
    deleteTree(root);  ///< Delete the entire tree
}

/**
 * @brief Copy constructor for the Bst class
 *
 * Creates a deep copy of another BST.
 *
 * @param other The BST to copy from.
 */
template <class T>
Bst<T>::Bst(const Bst<T>& other)
{
    if (this != &other) {
        root = copyTree(other.root);  ///< Deep copy the tree
    } else {
        root = nullptr;
    }
}

/**
 * @brief Assignment operator for the Bst class
 *
 * Performs a deep copy of another BST.
 *
 * @param other The BST to assign from.
 * @return A reference to the current object.
 */
template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other) {
        deleteTree(root);  ///< Delete current tree
        root = copyTree(other.root);  ///< Deep copy the tree
    }
    return *this;
}

/**
 * @brief Insert a value into the BST
 *
 * Calls the recursive insert function to add a value to the tree.
 *
 * @param value The value to insert into the tree.
 */
template <class T>
void Bst<T>::insert(T value)
{
    root = insertRecursive(root, value);  ///< Call the recursive insert
}

/**
 * @brief Recursive helper function to insert a value into the BST
 *
 * This function recursively finds the correct location to insert a new value in the tree.
 *
 * @param node The current node in the recursive search.
 * @param value The value to insert.
 * @return The updated node (with the inserted value).
 */
template <class T>
Node<T>* Bst<T>::insertRecursive(Node<T>* node, T value)
{
    if (node == nullptr)
        return new Node<T>(value);  ///< Create new node if reached empty spot

    if (value < node->data)
    {
        node->left = insertRecursive(node->left, value);  ///< Go left if value is smaller
    }
    else
    {
        node->right = insertRecursive(node->right, value);  ///< Go right if value is larger or equal
    }
    return node;  ///< Return the node (modified or unchanged)
}

/**
 * @brief Remove a value from the BST
 *
 * Calls the recursive remove function to delete a value from the tree.
 *
 * @param value The value to remove from the tree.
 */
template <class T>
void Bst<T>::remove(T value)
{
    root = deleteRecursive(root, value);  ///< Call the recursive delete
}

/**
 * @brief Recursive helper function to remove a value from the BST
 *
 * This function finds and deletes the specified value from the tree, handling the three cases:
 * - No children
 * - One child
 * - Two children (find the in-order successor)
 *
 * @param node The current node being examined.
 * @param value The value to remove.
 * @return The updated node (after removal).
 */
template <class T>
Node<T>* Bst<T>::deleteRecursive(Node<T>* node, T value)
{
    if (node == nullptr) {
        return nullptr;  ///< Value not found
    }

    if (value < node->data) {
        node->left = deleteRecursive(node->left, value);  ///< Go left
    }
    else if (value > node->data) {
        node->right = deleteRecursive(node->right, value);  ///< Go right
    }
    else {
        // Node to be deleted found
        if (node->left == nullptr) {
            Node<T>* temp = node->right;
            delete node;
            return temp;  ///< Replace with right child
        }
        else if (node->right == nullptr) {
            Node<T>* temp = node->left;
            delete node;
            return temp;  ///< Replace with left child
        }
        else {
            Node<T>* temp = findMin(node->right);  ///< Find in-order successor
            node->data = temp->data;
            node->right = deleteRecursive(node->right, temp->data);  ///< Delete the successor
        }
    }
    return node;
}

/**
 * @brief Search for a value in the BST
 *
 * Calls the recursive search function to find a value in the tree.
 *
 * @param value The value to search for.
 * @return `true` if the value is found, `false` otherwise.
 */
template <class T>
bool Bst<T>::search(T value)
{
    return searchRecursive(root, value);
}

/**
 * @brief Recursive helper function to search for a value in the BST
 *
 * This function recursively searches for a value in the tree.
 *
 * @param node The current node being examined.
 * @param value The value to search for.
 * @return The node containing the value, or nullptr if not found.
 */
template <class T>
Node<T>* Bst<T>::searchRecursive(Node<T>* node, T value)
{
    if (node == nullptr) {
        return nullptr;  ///< Value not found
    }
    if (node->data == value) {
        return node;  ///< Found the node
    }
    if (value < node->data) {
        return searchRecursive(node->left, value);  ///< Search left
    }
    else {
        return searchRecursive(node->right, value);  ///< Search right
    }
}

/**
 * @brief Count the number of nodes in the BST
 *
 * Calls the recursive count function to count all nodes in the tree.
 *
 * @return The total number of nodes in the tree.
 */
template <class T>
int Bst<T>::count() const
{
    return countNodesRecursive(root);
}

/**
 * @brief Recursive helper function to count the nodes in the tree
 *
 * This function recursively counts all the nodes in the tree.
 *
 * @param node The current node being examined.
 * @return The total number of nodes.
 */
template <class T>
int Bst<T>::countNodesRecursive(Node<T>* node) const
{
    if (node == nullptr) {
        return 0;  ///< Return 0 for nullptr (base case)
    }
    return 1 + countNodesRecursive(node->left) + countNodesRecursive(node->right);
}

/**
 * @brief Calculate the sum of all node values in the BST
 *
 * Calls the recursive sum function to calculate the total sum of the tree's nodes.
 *
 * @return The sum of all node values.
 */
template <class T>
T Bst<T>::sum() const
{
    return sumNodesRecursive(root);
}

/**
 * @brief Recursive helper function to calculate the sum of all node values
 *
 * This function recursively sums all the values stored in the tree's nodes.
 *
 * @param node The current node being examined.
 * @return The sum of all node values.
 */
template <class T>
T Bst<T>::sumNodesRecursive(Node<T>* node) const
{
    if (node == nullptr) {
        return T();  ///< Return default value (e.g., 0 for numeric types)
    }
    return node->data + sumNodesRecursive(node->left) + sumNodesRecursive(node->right);
}

/**
 * @brief Get the root node of the BST
 *
 * @return A pointer to the root node.
 */
template <class T>
Node<T>* Bst<T>::getRoot() const
{
    return root;
}

/**
 * @brief In-order traversal of the tree with a function pointer
 *
 * This function performs an in-order traversal of the tree and applies a given function
 * to each node's value.
 *
 * @param func The function to apply to each node's value.
 */
template <class T>
void Bst<T>::inOrder(void (*func)(T)) const
{
    inOrderRecursive(root, func);
}

/**
 * @brief Recursive in-order helper function
 *
 * This function recursively traverses the tree in in-order fashion and applies
 * the given function to each node's value.
 *
 * @param node The current node being examined.
 * @param func The function to apply to the node's data.
 */
template <class T>
void Bst<T>::inOrderRecursive(Node<T>* node, void (*func)(T)) const
{
    if (node != nullptr) {
        inOrderRecursive(node->left, func);  ///< Visit left subtree
        func(node->data);                    ///< Apply function to node data
        inOrderRecursive(node->right, func); ///< Visit right subtree
    }
}

/**
 * @brief Pre-order traversal of the tree with a function pointer
 *
 * This function performs a pre-order traversal of the tree and applies a given function
 * to each node's value.
 *
 * @param func The function to apply to each node's value.
 */
template <class T>
void Bst<T>::preOrder(void (*func)(T)) const
{
    preOrderRecursive(root, func);
}

/**
 * @brief Recursive pre-order helper function
 *
 * This function recursively traverses the tree in pre-order fashion and applies
 * the given function to each node's value.
 *
 * @param node The current node being examined.
 * @param func The function to apply to the node's data.
 */
template <class T>
void Bst<T>::preOrderRecursive(Node<T>* node, void (*func)(T)) const
{
    if (node != nullptr) {
        func(node->data);                    ///< Apply function to node data
        preOrderRecursive(node->left, func);  ///< Visit left subtree
        preOrderRecursive(node->right, func); ///< Visit right subtree
    }
}

/**
 * @brief Post-order traversal of the tree with a function pointer
 *
 * This function performs a post-order traversal of the tree and applies a given function
 * to each node's value.
 *
 * @param func The function to apply to each node's value.
 */
template <class T>
void Bst<T>::postOrder(void (*func)(T)) const
{
    postOrderRecursive(root, func);
}

/**
 * @brief Recursive post-order helper function
 *
 * This function recursively traverses the tree in post-order fashion and applies
 * the given function to each node's value.
 *
 * @param node The current node being examined.
 * @param func The function to apply to the node's data.
 */
template <class T>
void Bst<T>::postOrderRecursive(Node<T>* node, void (*func)(T)) const
{
    if (node != nullptr) {
        postOrderRecursive(node->left, func);  ///< Visit left subtree
        postOrderRecursive(node->right, func); ///< Visit right subtree
        func(node->data);                      ///< Apply function to node data
    }
}

/**
 * @brief Find the minimum node in a subtree
 *
 * This function finds the leftmost (minimum) node in a given subtree, which is
 * used for deleting a node with two children.
 *
 * @param node The current node being examined.
 * @return A pointer to the minimum node in the subtree.
 */
template <class T>
Node<T>* Bst<T>::findMin(Node<T>* node)
{
    while (node && node->left != nullptr)
        node = node->left;  ///< Move to the leftmost node
    return node;  ///< Return the minimum node
}

/**
 * @brief Delete the entire tree recursively
 *
 * This function recursively deletes all nodes in the tree, freeing up memory.
 *
 * @param node The current node being deleted.
 */
template <class T>
void Bst<T>::deleteTree(Node<T>* node)
{
    if (node != nullptr) {
        deleteTree(node->left);   ///< Delete left subtree
        deleteTree(node->right);  ///< Delete right subtree
        delete node;              ///< Delete the current node
    }
}

/**
 * @brief Copy the tree recursively
 *
 * This function creates a deep copy of a given subtree.
 *
 * @param node The current node being copied.
 * @return A pointer to the new node that is a copy of the given node.
 */
template <class T>
Node<T>* Bst<T>::copyTree(Node<T>* node)
{
    if (node == nullptr) {
        return nullptr;  ///< Return nullptr for empty node
    }
    Node<T>* newNode = new Node<T>(node->data);  ///< Create a new node
    newNode->left = copyTree(node->left);        ///< Copy left subtree
    newNode->right = copyTree(node->right);      ///< Copy right subtree
    return newNode;                              ///< Return the new node
}

#endif // BST_H_INCLUDED
