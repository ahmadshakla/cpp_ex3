//
// Created by ahmad.shakla on 9/15/19.
//
#include <iostream>
#include <iterator>
#include <map>
#include <list>
#include <vector>


#ifndef CPP_EX3_HPP
#define CPP_EX3_HPP

template<typename KeyT, typename ValueT>
class HashMap
{

private:
    std::vector<std::pair<KeyT, ValueT> > *_hashMap;
    double _lowerLoadFactor, _upperLoadFactor;
    int _capacity, _currSize;

    const size_t reIndex (size_t hashedIndex) const
    { return hashedIndex & (_capacity - 1); }

public:
    //-------------------------------------- constructors --------------------------------------
    explicit HashMap(double lowerLoadFactor = 0.25, double upperLoadFactor = 0.75)
            : _lowerLoadFactor(lowerLoadFactor), _upperLoadFactor(upperLoadFactor),
              _capacity{16}, _currSize(0)
    {
        _hashMap = new std::vector<std::pair<KeyT, ValueT> >[16];
    }

    HashMap(std::vector<KeyT> keysVec, std::vector<ValueT> valuesVec)
    // TODO exception
    {}

    //-------------------------------------- methods --------------------------------------

    /**
     * @return the number of elements in the map
     */
    const int size() const
    {

        return this->_currSize;
    }

    /**
     * @return the capacity of the map (the number of elements it can hold)
     */
    const int capacity() const
    { return this->_capacity; }

    /**
     * @return the load factor of the map, size/capacity
     */
    const double getLoadFactor() const
    { return (double) _currSize / _capacity; }

    /**
     * @return whether the map is empty or not
     */
    const bool empty() const
    { return !_currSize; }

    /**
     * adds a new pair to the map
     * @param key the key that we want to insert
     * @param value the value of the key
     * @return true if the item was added successfully, false otherwise
     */
    const bool insert(const KeyT &key, const ValueT &value)
    {
        if (containsKey(key))
        {
            return false;
        }
        std::pair<KeyT, ValueT> newPair(key, value);
        size_t hashedVal = std::hash<KeyT>{}(key);
        hashedVal = reIndex(hashedVal);
        _hashMap[hashedVal].push_back(newPair);
        ++_currSize;
        return true;
    }

    /**
     * checks if a certain key already exists in the map
     * @param key the key we want to check
     * @return true if it is already in the map. false otherwise.
     */
    bool containsKey(const KeyT &key) const
    {
        size_t hashedVal = std::hash<KeyT>{}(key);
        hashedVal = reIndex(hashedVal);

        for (const std::pair<KeyT, ValueT> &pair : _hashMap[hashedVal])
        {
            if (pair.first == key)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * gets the value of an element using the key
     * @param key the key of the element that we want to find it's value
     * @return the value of the given key
     */
     ValueT& at(const KeyT key)
    {
        size_t hashedVal = reIndex(std::hash<KeyT>{}(key));
        for ( std::pair<KeyT, ValueT> &pair : _hashMap[hashedVal])
        {
            if (pair.first == key)
            {
                return pair.second;
            }
        }
        throw std::out_of_range("map::at");
    }

    /**
     * removes an element with key "key" from the table
     * @param key
     * @return
     */
    bool erase(const KeyT &key)
    {
        if (!containsKey(key))
        {
            return false;
        }
        size_t hashedVal = std::hash<KeyT>{}(key);
        hashedVal = reIndex(hashedVal);
        for (int i = 0; i < _hashMap[hashedVal] ; ++i)
        {
            if (_hashMap[hashedVal][i].first == key)
            {
                _hashMap[hashedVal].erase(_hashMap[hashedVal].begin() + i);
                return true;
            }
        }
        return false;



    }


};


#endif //EX3_HASHMAP_HPP
