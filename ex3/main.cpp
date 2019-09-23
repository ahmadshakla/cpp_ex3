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

/**
 * a class representing the hashmap
 * @tparam KeyT the key in the map
 * @tparam ValueT the value in the map
 */
template<typename KeyT, typename ValueT>
class HashMap
{

private:
    std::vector<std::pair<KeyT, ValueT> > *_hashMap;
    double _lowerLoadFactor, _upperLoadFactor;
    int _capacity, _currSize;

    /**
     * @param hashedIndex the hash value we get from std::hash
     * @param mapCapacity the current capacity of the map.
     * @return an index in the range of the capacity of the map.
     */
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
            : _lowerLoadFactor(0.25), _upperLoadFactor(0.75),
              _capacity{16}, _currSize(0)
    {
        _hashMap = new std::vector<std::pair<KeyT, ValueT> >[16];

        if (keysVec.size() != valuesVec.size())
        {
            // TODO exception
            throw 0;
        }
        for (int i = 0; i < keysVec.size(); ++i)
        {
            insert(keysVec[i], valuesVec[i]);
        }
    }

    /**
     * copy constructor
     * @param other the other object we want to copy from
     */
    HashMap(HashMap<KeyT, ValueT> &other)
            :
            _lowerLoadFactor(other._lowerLoadFactor),
            _upperLoadFactor(other._upperLoadFactor),
            _capacity(other._capacity),
            _currSize(0)
    {
        _hashMap = new std::vector<std::pair<KeyT, ValueT> >[other._capacity];
        for (const auto &pair : other)
        {
            insert(pair.first, pair.second);
        }
    }

    /**
     * move constructor
     * @param other the other object that we want to *steal* from
     */
    HashMap(HashMap &&other) noexcept :

            _hashMap(std::move(other._hashMap)),
            _lowerLoadFactor(std::move(other._lowerLoadFactor)),
            _upperLoadFactor(std::move(other._upperLoadFactor)),
            _capacity(std::move(other.capacity())), _currSize(other._currSize)
    {
        other._hashMap = nullptr;
//        other = nullptr;
    };

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
    ValueT &at(const KeyT key) const
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

    //-------------------------------------- operators --------------------------------------

    /**
     * the assignment operator
     * @param other the map we want to assign from
     * @return the new assigned to map
     */
    HashMap &operator=(HashMap &other)
    {
        //TODO check why it cant be const
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_currSize, other._currSize);
        std::swap(this->_upperLoadFactor, other._upperLoadFactor);
        std::swap(this->_lowerLoadFactor, other._lowerLoadFactor);
        std::swap(this->_hashMap, other._hashMap);
        return *this;
    }

    /**
     * the brackets operator for assigning
     * @param index the key we want to find it's value
     * @return a reference to the value of that key
     */
    ValueT &operator[](const KeyT &index)
    {
        size_t hashedVal = std::hash<KeyT>{}(index);
        hashedVal = _reIndex(hashedVal, _capacity);
        if (containsKey(index))
        {
            for (auto &pair: _hashMap[hashedVal])
            {
                if (pair.first == index)
                {
                    return pair.second;
                }
            }

            std::pair<KeyT, ValueT> newPair(index, ValueT{});
            insert(newPair.first, newPair.second);
            return at(newPair.first);
        }
        else
        {
            std::pair<KeyT, ValueT> newPair(index, ValueT{});
            insert(newPair.first, newPair.second);
            return at(newPair.first);
        }

    }

    /**
    * the brackets operator for reading
    * @param index the key we want to find it's value
    * @return a reference to the value of that key
    */
    const ValueT &operator[](const KeyT &index) const
    {
        size_t hashedVal = std::hash<KeyT>{}(index);
        hashedVal = _reIndex(hashedVal, _capacity);
        if (containsKey(index))
        {
            for (const auto &pair: _hashMap[hashedVal])
            {
                if (pair.first == index)
                {
                    return pair.second;
                }
            }
        }
        else
        {
            std::pair<KeyT, ValueT> newPair(index, ValueT{});
            insert(newPair.first, newPair.second);
            return at(newPair.first);
        }
    }

    /**
    * the  equals operator
    * @param rhs the operator we wish to compare with
    * @return false if they are not equal, true if they are
    */
    const bool operator==(const HashMap &other)
    {
        if (this->_currSize != other.size() || this->_upperLoadFactor != other._upperLoadFactor ||
            this->_lowerLoadFactor != other._lowerLoadFactor || this->_capacity != other._capacity)
        {
            return false;
        }
        for (const auto &pair:*this)
        {
            if (!other.containsKey(pair.first))
            {
                return false;
            }
            if (pair.second != other.at(pair.first))
            {
                return false;
            }
        }
        return true;
    }

    /**
    * the not equals operator
    * @param rhs the operator we wish to compare with
    * @return true if they are not equal, false if they are
    */
    const bool operator!=(const HashMap &other)
    {
        return !(*this == other);
    }

    //-------------------------------------- iterator --------------------------------------

    /**
     * the iterator class
     */
    class iterator
    {
    private:
        std::pair<KeyT, ValueT> *_pointer;
        HashMap<KeyT, ValueT> *_myMap;

        /**
         * a function that takes a pair of key and value and returns it's index in the
         * map
         * @param pair the pair we want to find
         * @return the index represented as pair of size_t
         */
        std::pair<size_t, size_t> _getIndexOfItem(std::pair<KeyT, ValueT> pair)
        {
            size_t hashedVal = std::hash<KeyT>{}(pair.first);
            hashedVal = hashedVal & (_myMap->capacity() - 1);
            for (int i = 0; i < _myMap->_hashMap[hashedVal].size(); ++i)
            {
                if (pair.first == _myMap->_hashMap[hashedVal][i].first)
                {
                    return std::pair<int, int>(hashedVal, i);
                }
            }
            return std::pair<int, int>();
        }

    public:
        /**
         * the iterators constructor, that initializes a new iterator
         * @param N a pointer to the pair we are at at the moment
         * @param  a pointer to  myMap the hashmap object that we are in.
         */
        explicit iterator(std::pair<KeyT, ValueT> *N = nullptr,
                          HashMap<KeyT, ValueT> *myMap = nullptr) : _pointer(N),
                                                                    _myMap(myMap) {}

        /**
         * the * operator
         * @return the a pointer to the pair
         */
        std::pair<KeyT, ValueT> &operator*() const { return *_pointer; }

        /**
         * the -> operator
         * @return the pair
         */
        std::pair<KeyT, ValueT> *operator->() const { return _pointer; }

        /**
         * the prefix increment operator
         * @return  an iterator to the next element
         */
        iterator &operator++()
        {
            if (_getIndexOfItem(*_pointer).second <
                _myMap->_hashMap[_getIndexOfItem(*_pointer).first].size() - 1)
            {
                _pointer = &(_myMap->_hashMap[_getIndexOfItem(*_pointer).first][
                        _getIndexOfItem(*_pointer).second + 1]);
            }
            else
            {
                bool flag = false;
                for (size_t i = _getIndexOfItem(*_pointer).first + 1; i < _myMap->capacity(); ++i)
                {
                    for (auto &item:_myMap->_hashMap[i])
                    {
                        _pointer = &item;
                        flag = true;
                        break;
                    }
                    if (flag)
                    {
                        break;
                    }
                }
                if (!flag)
                {
                    _pointer = nullptr;
                }
            }
            return *this;
        }

        /**
         * the postfix increment operator
         * @return  an iterator to the next element
         */
        const HashMap::iterator operator++(int)
        {
            iterator &temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * the not equals operator
         * @param rhs the operator we wish to compare with
         * @return true if they are not equal, false if they are
         */
        bool operator!=(iterator const &rhs) const { return _pointer != rhs._pointer; }


        /**
        * the  equals operator
        * @param rhs the operator we wish to compare with
        * @return false if they are not equal, true if they are
        */
        bool operator==(iterator const &rhs) const { return _pointer == rhs._pointer; }
    };

//    using const_iterator = iterator;

    /**
     * @return an iterator to the first element to the map
     */
    iterator begin()
    {
        for (int i = 0; i < capacity(); ++i)
        {
            for (const auto &item:_hashMap[i])
            {
                return iterator(&item, this);
            }
        }
        return iterator();
    }

    /**
     * @return an iterator to the last element of the map
     */
    iterator end()
    {
        return iterator(nullptr);
    }


};


#endif //EX3_HASHMAP_HPP
