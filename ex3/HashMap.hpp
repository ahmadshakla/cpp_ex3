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

    const size_t _reIndex(size_t hashedIndex, int mapCapacity) const
    {
        return hashedIndex & (mapCapacity - 1);
    }

    /**
     * rehashes all the elements of the map to a new map with bigger / smaller size, depending
     * on the upper / lower factor.
     * @param newSize the new size we want to give to the new map
     */
    void _reHash(int newSize)
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
                    hashedVal = _reIndex(hashedVal, newSize);
                    newHashMap[hashedVal].push_back(pair);
                }
            }
            _capacity = newSize;
            delete[] _hashMap;
            _hashMap = newHashMap;
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

    ~HashMap()
    {
        delete[] _hashMap;
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
        hashedVal = _reIndex(hashedVal, _capacity);
        _hashMap[hashedVal].push_back(newPair);
        ++_currSize;
        if (getLoadFactor() > _upperLoadFactor)
        {
            _reHash(2 * _capacity);
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
        hashedVal = _reIndex(hashedVal, _capacity);

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
        size_t hashedVal = _reIndex(std::hash<KeyT>{}(key), _capacity);
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
        hashedVal = _reIndex(hashedVal, _capacity);
        for (int i = 0; i < _hashMap[hashedVal].size(); ++i)
        {
            if (_hashMap[hashedVal][i].first == key)
            {
                _hashMap[hashedVal].erase(_hashMap[hashedVal].begin() + i);
                --_currSize;
                if (getLoadFactor() < _lowerLoadFactor)
                {
                    _reHash(_capacity / 2);
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
        hashedIndex = _reIndex(hashedIndex, _capacity);
        return (int) _hashMap[hashedIndex].size();
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

    //-------------------------------------- iterator --------------------------------------

    class iterator
    {
    private:
        std::pair<KeyT, ValueT> *_pointer;
        HashMap<KeyT, ValueT> *_myMap;
        std::pair<size_t, size_t> getIndexOfItem(std::pair<KeyT, ValueT> pair)
        {
            size_t hashedVal = std::hash<KeyT>{}(pair.first);
            hashedVal = hashedVal & (_myMap->capacity() - 1);
            for (int i = 0; i < _myMap->_hashMap[hashedVal].size(); ++i)
            {
                if(pair.first ==  _myMap->_hashMap[hashedVal][i].first)
                {
                    return std::pair<int ,int>(hashedVal,i);
                }
            }
        }

    public:
        explicit iterator(std::pair<KeyT, ValueT> *N = nullptr,
                          HashMap<KeyT, ValueT> *myMap = nullptr) : _pointer(N), _myMap(myMap)
        {}

        std::pair<KeyT, ValueT> &operator*() const
        { return *_pointer; }

        std::pair<KeyT, ValueT> *operator->() const
        { return &*_pointer; }
        iterator& operator++()
        {
            if(getIndexOfItem(*_pointer).second < _myMap->_hashMap[getIndexOfItem(*_pointer).first].size()-1 )
            {
                _pointer = &(_myMap->_hashMap[getIndexOfItem(*_pointer).first][getIndexOfItem(*_pointer).second + 1]);
            }
            else{
                bool flag = false;
                for (size_t i = getIndexOfItem(*_pointer).first + 1 ; i < _myMap->capacity(); ++i)
                {
                    for (auto &item:_myMap->_hashMap[i])
                    {
                        _pointer = &item;
                        flag = true;
                        break;
                    }
                    if(flag)
                    {
                        break;
                    }
                }
                if (!flag)
                {
                    _pointer =  nullptr;
                }
            }
            return *this;
        }
        iterator& operator++(int)
        {
            iterator &temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(iterator const& rhs) const
        { return _pointer != rhs._pointer; }
    };


    iterator begin()
    {
        for (int i = 0; i < capacity(); ++i)
        {
            for (auto &item:_hashMap[i])
            {
                return iterator(&item, this);
            }
        }
        return iterator();
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    //-------------------------------------- operators --------------------------------------

    HashMap& operator=(HashMap &other)
    {
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_currSize,other._currSize);
        std::swap(this->_upperLoadFactor , other._upperLoadFactor);
        std::swap(this->_lowerLoadFactor,other._lowerLoadFactor);
        std::swap(this->_hashMap,other._hashMap);
        return *this;
    }

    ValueT &operator[](const KeyT &index)
    {
        size_t hashedVal = std::hash<KeyT>{}(index);
        hashedVal = _reIndex(hashedVal, _capacity);
        if (containsKey(index))
        {
            for (auto &pair: _hashMap[hashedVal])
            {
                if(pair.first == index)
                {
                    return pair.second;
                }
            }

            std::pair<KeyT,ValueT> newPair(index,ValueT{});
            _hashMap[hashedVal].push_back(newPair);
            return newPair.second;
        }
        else
        {
            std::pair<KeyT,ValueT> newPair(index,ValueT{});
            _hashMap[hashedVal].push_back(newPair);
            return newPair.second;
        }

    }

    const ValueT &operator[](const KeyT &index) const
    {
        size_t hashedVal = std::hash<KeyT>{}(index);
        hashedVal = _reIndex(hashedVal, _capacity);
        if (containsKey(index))
        {
            for (const auto &pair: _hashMap[hashedVal])
            {
                if(pair.first == index)
                {
                    return pair.second;
                }
            }
        }
        else
        {
            std::pair<KeyT,ValueT> newPair(index,ValueT{});
            _hashMap[hashedVal].push_back(newPair);
            return newPair.second;
        }
    }




};


#endif //EX3_HASHMAP_HPP
