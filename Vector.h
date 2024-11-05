#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <vector>

using std::vector;

//const int INITIAL_SIZE = 6; Initial array size not needed in STL

template <class T>
class Vector
{
public:
    Vector();                               // Default constructor
    Vector(int n);                           // Constructor with specified initial capacity
    Vector(const Vector<T>& other);          // Copy constructor
    Vector<T>& operator=(const Vector<T>& other);  // Assignment operator
    ~Vector();                              // Destructor

    const T& operator[](int n) const;
    bool Add(T element);                    // Adds element to the end of the vector
    bool Remove();                          // Removes last element
    bool Insert(int index, T element);      // Inserts element at specified index
    bool Delete(int index);                 // Deletes element at specified index
    bool Modify(int index, T element);      // Modifies element at specified index
    int size() const;                       // Get current number of elements
    const T& at(int n) const;               // Access element at specified index
    bool isEmpty() const;                   // Checks if vector is empty

private:
    vector<T> m_array;  // STL vector used to store elements
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
