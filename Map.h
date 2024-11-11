#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <map>

using std::map;

template <class T, class U>
class Map
{
public:
    void insert(const T& key, const U& value);    // Insert a key-value pair
    U get(const T& key) const;    // Get the value associated with a key
    bool exists(const T& key) const;    // Check if the key exists in the map
    int size() const;    // Get the size of the map

private:
    map<T, U> m_map;  // Underlying std::map to store key-value pairs
};

template <class T, class U>
void Map<T, U>::void insert(const T& key, const U& value)
{
    m_map[key] = value;
}

template <class T, class U>
U Map<T, U>::get(const T& key) const
{
    // If the key doesn't exist, throw an exception
    auto iter = m_map.find(key);
    if (iter == m_map.end())
    {
        return U(); // return empty value
    }
    return iter->second;
}

template <class T, class U>
bool Map<T, U>::exists(const T& key) const
{
    return m_map.find(key) != m_map.end();
}

template <class T, class U>
int Map<T, U>::size() const
{
    return m_map.size();
}

#endif // MAP_H_INCLUDED
