#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <vector>

using std::vector;

/**
 * @class Vector
 * @brief A custom implementation of a dynamic array
 *
 * This class provides a template-based wrapper around the standard `std::vector` to manage
 * elements in a dynamic array, allowing users to add, remove, insert, modify, and access elements.
 * It also provides utility functions such as checking the size and whether the vector is empty.
 *
 * @tparam T The type of elements stored in the vector (e.g., int, double, etc.)
 *
 * @author Max Wong
 * @version 1.0
 * @date 11 Nov 2024
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Default constructor
     *
     * Initializes an empty vector.
     */
    Vector();

    /**
     * @brief Constructor with specified initial capacity
     *
     * Initializes the vector with an initial capacity to store `n` elements.
     *
     * @param n The initial capacity of the vector.
     */
    Vector(int n);

    /**
     * @brief Copy constructor
     *
     * Creates a new vector by copying the contents of another vector.
     *
     * @param other The vector to copy.
     */
    Vector(const Vector<T>& other);

    /**
     * @brief Assignment operator
     *
     * Assigns the contents of one vector to another.
     *
     * @param other The vector to assign from.
     * @return A reference to the current vector object.
     */
    Vector<T>& operator=(const Vector<T>& other);

    /**
     * @brief Destructor
     *
     * Frees the memory used by the vector.
     */
    ~Vector();

    /**
     * @brief Access element by index
     *
     * Provides read-only access to the element at the specified index.
     *
     * @param n The index of the element to access.
     * @return A constant reference to the element at index `n`.
     */
    const T& operator[](int n) const;

    /**
     * @brief Adds an element to the end of the vector
     *
     * Adds the specified element to the end of the vector, increasing its size by one.
     *
     * @param element The element to add.
     * @return `true` if the element was successfully added, always `true` in this implementation.
     */
    bool Add(T element);

    /**
     * @brief Removes the last element from the vector
     *
     * Removes the most recently added element from the vector.
     *
     * @return `true` if an element was successfully removed, `false` if the vector is empty.
     */
    bool Remove();

    /**
     * @brief Inserts an element at a specified index
     *
     * Inserts the specified element at the given index, shifting subsequent elements.
     *
     * @param index The index where the element should be inserted.
     * @param element The element to insert.
     * @return `true` if the element was successfully inserted, `false` if the index is invalid.
     */
    bool Insert(int index, T element);

    /**
     * @brief Deletes an element at a specified index
     *
     * Deletes the element at the specified index and shifts subsequent elements.
     *
     * @param index The index of the element to delete.
     * @return `true` if the element was successfully deleted, `false` if the index is invalid.
     */
    bool Delete(int index);

    /**
     * @brief Modifies an element at a specified index
     *
     * Changes the value of the element at the given index.
     *
     * @param index The index of the element to modify.
     * @param element The new value for the element at the given index.
     * @return `true` if the element was successfully modified, `false` if the index is invalid.
     */
    bool Modify(int index, T element);

    /**
     * @brief Gets the current number of elements in the vector
     *
     * Returns the size of the vector (the number of elements stored).
     *
     * @return The current number of elements in the vector.
     */
    int size() const;

    /**
     * @brief Access element at a specified index
     *
     * Provides bounds-checked access to an element at the specified index.
     * Throws an exception if the index is out of bounds.
     *
     * @param n The index of the element to access.
     * @return A constant reference to the element at the given index.
     * @throw std::out_of_range If the index is out of bounds.
     */
    const T& at(int n) const;

    /**
     * @brief Checks if the vector is empty
     *
     * Returns `true` if the vector has no elements, otherwise returns `false`.
     *
     * @return `true` if the vector is empty, `false` otherwise.
     */
    bool isEmpty() const;

private:
    vector<T> m_array; ///< The underlying STL vector used to store the elements
};

template <class T>
Vector<T>::Vector() {}

template <class T>
Vector<T>::Vector(int n)
{
    m_array.reserve(n);  // Reserve space for n elements
}

template <class T>
Vector<T>::~Vector() {}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : m_array(other.m_array) {}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
        m_array = other.m_array;
    return *this;
}

template <class T>
const T& Vector<T>::operator[](int n) const
{
    return m_array[n];  // Access element at index n
}

template <class T>
bool Vector<T>::Add(T element)
{
    m_array.push_back(element);  // Use STL vector's push_back method
    return true;
}

template <class T>
bool Vector<T>::Remove()
{
    if (!m_array.empty())
    {
        m_array.pop_back();  // Use STL vector's pop_back method
        return true;
    }
    return false;  // No element to remove
}

template <class T>
bool Vector<T>::Insert(int index, T element)
{
    if (index >= 0 && index <= m_array.size())
    {
        m_array.insert(m_array.begin() + index, element);  // Insert element at index
        return true;
    }
    return false;  // Invalid index
}

template <class T>
bool Vector<T>::Delete(int index)
{
    if (index >= 0 && index < m_array.size())
    {
        m_array.erase(m_array.begin() + index);  // Delete element at index
        return true;
    }
    return false;  // Invalid index
}

template <class T>
bool Vector<T>::Modify(int index, T element)
{
    if (index >= 0 && index < m_array.size())
    {
        m_array[index] = element;  // Modify element at index
        return true;
    }
    return false;  // Invalid index
}

template <class T>
int Vector<T>::size() const
{
    return m_array.size();  // Use STL vector's size method
}

template <class T>
const T& Vector<T>::at(int n) const
{
    return m_array.at(n);  // Use STL vector's at() method for bounds checking
}

template <class T>
bool Vector<T>::isEmpty() const
{
    return m_array.empty();  // Use STL vector's empty() method
}

#endif // VECTOR_H_INCLUDED
