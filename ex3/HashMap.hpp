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
    std::vector<std::pair<KeyT,ValueT> > *_hashMap ;
    double _lowerLoadFactor, _upperLoadFactor;
    int _capacity, _currSize;
    size_t reIndex(size_t hashedIndex){ return hashedIndex & (_capacity -1);}
public:
    //-------------------------------------- constructors --------------------------------------
    explicit HashMap(double lowerLoadFactor = 0.25, double upperLoadFactor = 0.75)
            : _lowerLoadFactor(lowerLoadFactor), _upperLoadFactor(upperLoadFactor),
              _capacity{16}, _currSize(0)
    {
        _hashMap = new std::vector<std::pair<KeyT,ValueT> >[16];
    }

    HashMap(std::vector<KeyT> keysVec, std::vector<ValueT> valuesVec)
    // TODO exception
    {}

    //-------------------------------------- methods --------------------------------------

    /**
     * @return the number of elements in the map
     */
    int size() {

        return this->_currSize;
    }

    /**
     * @return the capacity of the map (the number of elements it can hold)
     */
    int capacity() { return this->_capacity; }

    /**
     * @return the load factor of the map, size/capacity
     */
    double getLoadFactor() { return (double) _currSize / _capacity; }

    /**
     * @return whether the map is empty or not
     */
    bool empty() { return !_currSize; }

    /**
     * adds a new pair to the map
     * @param key the key that we want to insert
     * @param value the value of the key
     * @return true if the item was added successfully, false otherwise
     */
    bool insert(KeyT key,ValueT value)
    {
        if (containsKey(key))
        {
            return false;
        }
        std::pair<KeyT,ValueT> newPair(key,value);
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
    bool containsKey(KeyT key)
    {
        for (int i = 0; i < _capacity; ++i)
        {
            for (const std::pair<KeyT,ValueT> & pair : _hashMap[i])
            {
                if (pair.first == key)
                {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * gets the value of an element using the key
     * @param key the key of the element that we want to find it's value
     * @return the value of the given key
     */
    ValueT at(KeyT key)
    {
        // TODO exception

    }




};


#endif //EX3_HASHMAP_HPP
