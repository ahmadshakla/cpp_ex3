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

    const size_t reIndex(size_t hashedIndex, int mapCapacity) const
    {
        return hashedIndex & (mapCapacity - 1);
    }

    /**
     * rehashes all the elements of the map to a new map with bigger / smaller size, depending
     * on the upper / lower factor.
     * @param newSize the new size we want to give to the new map
     */
    void reHash(int newSize)
    {
        if (newSize >= 1)
        {
            std::vector<std::pair<KeyT, ValueT> > *newHashMap;
            newHashMap = new std::vector<std::pair<KeyT, ValueT> >[newSize];

            for (int i = 0; i < _capacity; ++i)
            {
                for (const std::pair<KeyT, ValueT> &pair : _hashMap[i])
                {
                    size_t hashedVal = std::hash<KeyT>{}(pair.first);
                    hashedVal = reIndex(hashedVal, newSize);
                    newHashMap[hashedVal].push_back(pair);
                }
            }
            _capacity = newSize;
            delete[] _hashMap;
            _hashMap = newHashMap;
        }
    }

     std::pair<size_t ,size_t > findPair(std::pair<KeyT, ValueT> *givenPair)
    {
        size_t hashedVal = std::hash<KeyT>{}(givenPair->first);
        hashedVal = reIndex(hashedVal, _capacity);
        for (size_t i = 0; i < _hashMap[hashedVal].size(); ++i)
        {
            if (_hashMap[hashedVal][i] == givenPair->first)
            {
                std::pair<size_t ,size_t > myPair(hashedVal, i);
                return myPair;
            }
        }
    }

public:
    //-------------------------------------- constructors --------------------------------------
    explicit HashMap(double lowerLoadFactor = 0.25, double upperLoadFactor = 0.75)
            : _lowerLoadFactor(lowerLoadFactor), _upperLoadFactor(upperLoadFactor),
              _capacity{16}, _currSize(0)
    {
        if (lowerLoadFactor > upperLoadFactor || upperLoadFactor > 1 || upperLoadFactor < 0 ||
            lowerLoadFactor < 0 || lowerLoadFactor > 1)
        {
            // TODO exception
        }
        _hashMap = new std::vector<std::pair<KeyT, ValueT> >[16];
    }

    HashMap(std::vector<KeyT> keysVec, std::vector<ValueT> valuesVec)
    {
        if (keysVec.size() != valuesVec.size())
        {
            // TODO exception
        }
        HashMap();
        for (int i = 0; i < keysVec.size(); ++i)
        {
            insert(keysVec[i], valuesVec[i]);
        }
    }

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
    const int capacity() const { return this->_capacity; }

    /**
     * @return the load factor of the map, size/capacity
     */
    const double getLoadFactor() const { return (double) _currSize / _capacity; }

    /**
     * @return whether the map is empty or not
     */
    const bool empty() const { return !_currSize; }

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
        hashedVal = reIndex(hashedVal, _capacity);
        _hashMap[hashedVal].push_back(newPair);
        ++_currSize;
        if (getLoadFactor() > _upperLoadFactor)
        {
            reHash(2 * _capacity);
        }
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
        hashedVal = reIndex(hashedVal, _capacity);

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
    ValueT &at(const KeyT key)
    {
        size_t hashedVal = reIndex(std::hash<KeyT>{}(key), _capacity);
        for (std::pair<KeyT, ValueT> &pair : _hashMap[hashedVal])
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
        hashedVal = reIndex(hashedVal, _capacity);
        for (int i = 0; i < _hashMap[hashedVal].size(); ++i)
        {
            if (_hashMap[hashedVal][i].first == key)
            {
                _hashMap[hashedVal].erase(_hashMap[hashedVal].begin() + i);
                --_currSize;
                if (getLoadFactor() < _lowerLoadFactor)
                {
                    reHash(_capacity / 2);
                }
                return true;
            }
        }
        return false;
    }

    /**
     * returns the size of the bucket that the wanted key exists in
     * @param key the key the we want to get it's bucket size
     * @return the number of elements in that bucket
     */
    const int bucketSize(const KeyT &key) const
    {
        size_t hashedIndex = std::hash<KeyT>{}(key);
        hashedIndex = reIndex(hashedIndex, _capacity);
        return _hashMap[hashedIndex].size();
    }

    /**
     * clears all the map, doesn't affect the capacity.
     */
    void clear()
    {
        for (int i = 0; i < _capacity; ++i)
        {
            _hashMap[i].clear();
        }
        _currSize = 0;
    }

    class iterator
    {
    private:
        std::pair<KeyT, ValueT> *_pointer;
    public:
        explicit iterator(std::pair<KeyT, ValueT> *N = nullptr) : _pointer(N) {}

        std::pair<KeyT, ValueT> &operator*() const { return *_pointer; }

        std::pair<KeyT, ValueT> *operator->() const { return _pointer; }


    };

    iterator begin()
    {
        for (int i = 0; i < capacity(); ++i)
        {
            for (std::pair<KeyT, ValueT> &pair : _hashMap[i])
            {
                return iterator(&pair);
            }
        }
    }

    iterator end()
    {
        return nullptr;
    }


};


#endif //EX3_HASHMAP_HPP
