#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>

const int INITIAL_SIZE = 6; // Initial array size

/**
 * @class Vector
 * @brief Template class implementing a dynamic array
 *
 * A custom implementation of a resizable array container,
 * similar to std::vector but with simplified functionality.
 *
 * @tparam T Type of elements stored in the vector
 *
 * @author Max Wong
 * @version 02
 * @date 11 Oct 2024
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Default constructor
     *
     * Creates an empty vector with initial capacity of INITIAL_SIZE
     */
    Vector();

    /**
     * @brief Constructor with specified initial capacity
     *
     * @param n Initial capacity of the vector
     * @pre n must be greater than 0
     */
    Vector(int n);

    /**
     * @brief Destructor
     *
     * Deallocates dynamic memory used by the vector
     */
    ~Vector();

    /**
     * @brief Copy constructor
     *
     * Creates a deep copy of another vector
     *
     * @param other Vector to copy from
     */
    Vector(const Vector<T>& other);

    /**
     * @brief Copy assignment operator
     *
     * Creates a deep copy of another vector
     *
     * @param other Vector to copy from
     * @return Reference to this vector
     */
    Vector<T>& operator=(const Vector<T>& other);

    /**
     * @brief Array subscript operator
     *
     * Access element at specified index
     *
     * @param n Index of element to access
     * @return Const reference to element at index n
     * @pre n must be within bounds of vector
     */
    const T& operator[](int n) const;

    /**
     * @brief Adds element to end of vector
     *
     * Automatically resizes if necessary
     *
     * @param element Element to add
     * @return true if successful, false otherwise
     */
    bool push_back(T element);

    /**
     * @brief Removes last element from vector
     *
     * @return true if element was removed, false if vector was empty
     */
    bool pop_back();

    /**
     * @brief Gets current number of elements
     *
     * @return Number of elements in vector
     */
    int size() const;

    /**
     * @brief Access element at specified index
     *
     * @param n Index of element to access
     * @return Const reference to element at index n
     * @pre n must be within bounds of vector
     */
    const T& at(int n) const;

    /**
     * @brief Checks if vector is empty
     *
     * @return true if vector contains no elements, false otherwise
     */
    bool isEmpty() const;

private:
    T *m_array;                                    ///< Pointer to the dynamic array
    int m_numElements;                             ///< The number of elements in the array
    int m_capacity;                                ///< Size of the actual array

    /**
     * @brief Resizes internal array
     *
     * @param newCapacity New capacity for array
     * @pre newCapacity must be greater than current capacity
     */
     void resize(int newCapacity);

};

template<class T>
Vector<T>::Vector()
{
    m_numElements = 0;
    m_capacity = INITIAL_SIZE;
    m_array = new T[m_capacity]; // Allocate memory for the initial size
}
template<class T>
Vector<T>::Vector(int n)
{
    m_numElements = 0;
    m_capacity = n;
    m_array = new T[m_capacity]; // Allocate memory for the specified size
}
template<class T>
Vector<T>::~Vector()
{
    delete[] m_array; // Deallocate memory
}
// Copy constructor for deep copying
template<class T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_numElements = other.m_numElements;
    m_capacity = other.m_capacity;
    m_array = new T[m_capacity];            // Allocate memory
    for (int i = 0; i < m_numElements; i++)
        m_array[i] = other.m_array[i];      // Copy elements
}
// Copy assignment operator
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (other.m_array != m_array)
    {
        delete[] m_array;                   // Deallocate current array
        m_numElements = other.m_numElements;
        m_capacity = other.m_capacity;
        m_array = new T[m_capacity];        // Allocate new memory
        for (int i = 0; i < m_numElements; i++)
            m_array[i] = other.m_array[i];  // Copy elements
    }
    return *this; // Return the current object
}
// Access element at index n
template <class T>
const T& Vector<T>::operator[](int n) const
{
    return m_array[n];
}
// Add element to the end of the vector
template <class T>
bool Vector<T>::push_back(T element)
{
    if (m_numElements >= m_capacity)
        resize(m_capacity * 2);         // Resize if capacity is reached
    m_array[m_numElements] = element;   // Add the new element
    m_numElements++;
    return true;
}
// Remove the last element from the vector
template <class T>
bool Vector<T>::pop_back()
{
    if (m_numElements > 0)
    {
        m_numElements--;    // Reduce the count of elements
        return true;
    }
    return false;           // Nothing to remove
}
// Resize array
template <class T>
void Vector<T>::resize(int newCapacity)
{
    T *tempArray = new T[newCapacity];      // Create a new array with the new capacity
    for (int i = 0; i < m_numElements; i++)
        tempArray[i] = m_array[i];          // Copy elements to the new array
    delete[] m_array;                       // Deallocate the old array
    m_array = tempArray;                    // Point to the new array
    m_capacity = newCapacity;               // Update capacity
}
// Access element at specific index
template <class T>
const T& Vector<T>::at(int n) const
{
    return m_array[n];
}
// Get number of elements in the array
template <class T>
int Vector<T>::size() const
{
    return m_numElements;
}
// Check if the vector is empty
template <class T>
bool Vector<T>::isEmpty() const
{
    return (m_numElements == 0);
}


#endif // VECTOR_H_INCLUDED
