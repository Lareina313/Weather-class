#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <map>

using std::map;

/**
 * @class Map
 * @brief A simple template-based wrapper around the STL map container
 *
 * This class provides a basic interface for working with key-value pairs using a `std::map`.
 * It supports basic operations like inserting key-value pairs, retrieving values by key,
 * checking if a key exists, and getting the size of the map.
 *
 * @tparam T The type of the key in the map.
 * @tparam U The type of the value associated with the key.
 */
template <class T, class U>
class Map
{
public:
    /**
     * @brief Inserts a key-value pair into the map
     *
     * This method inserts a key-value pair into the underlying map. If the key already
     * exists, the value is updated to the new value.
     *
     * @param key The key to insert.
     * @param value The value to associate with the key.
     */
    void insert(const T& key, const U& value);

    /**
     * @brief Retrieves the value associated with a given key
     *
     * This method returns the value associated with the provided key. If the key is not
     * found in the map, it returns a default-constructed value of type `U`.
     *
     * @param key The key whose associated value is to be retrieved.
     * @return The value associated with the key, or a default value if the key is not found.
     */
    U get(const T& key) const;

    /**
     * @brief Checks if a given key exists in the map
     *
     * This method checks whether the specified key exists in the map.
     *
     * @param key The key to check for existence.
     * @return `true` if the key exists, `false` otherwise.
     */
    bool exists(const T& key) const;

    /**
     * @brief Retrieves the size of the map
     *
     * This method returns the number of key-value pairs currently in the map.
     *
     * @return The number of key-value pairs in the map.
     */
    int size() const;

private:
    map<T, U> m_map;  ///< Underlying `std::map` to store key-value pairs
};

/**
 * @brief Inserts a key-value pair into the map
 *
 * This function inserts a key-value pair into the underlying `std::map`. If the key already
 * exists, the value is updated with the new value.
 *
 * @param key The key to insert.
 * @param value The value to associate with the key.
 */
template <class T, class U>
void Map<T, U>::insert(const T& key, const U& value)
{
    m_map[key] = value;  ///< Insert or update the key-value pair
}

/**
 * @brief Retrieves the value associated with the given key
 *
 * This function searches the map for the provided key and returns the associated value.
 * If the key is not found, it returns a default-constructed value of type `U`.
 *
 * @param key The key whose associated value is to be retrieved.
 * @return The value associated with the key, or a default value if the key is not found.
 */
template <class T, class U>
U Map<T, U>::get(const T& key) const
{
    // If the key doesn't exist, return an empty (default-constructed) value
    auto iter = m_map.find(key);
    if (iter == m_map.end())
    {
        return U();  ///< Return the default value of type U (e.g., 0 for numeric types)
    }
    return iter->second;  ///< Return the associated value
}

/**
 * @brief Checks if the given key exists in the map
 *
 * This function checks whether the specified key exists in the map. It returns `true`
 * if the key is found, otherwise it returns `false`.
 *
 * @param key The key to check for existence.
 * @return `true` if the key exists in the map, `false` otherwise.
 */
template <class T, class U>
bool Map<T, U>::exists(const T& key) const
{
    return m_map.find(key) != m_map.end();  ///< Check if key is present in the map
}

/**
 * @brief Returns the size of the map
 *
 * This function returns the number of key-value pairs in the map.
 *
 * @return The number of key-value pairs in the map.
 */
template <class T, class U>
int Map<T, U>::size() const
{
    return m_map.size();  ///< Return the size of the map
}

#endif // MAP_H_INCLUDED
