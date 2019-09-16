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

    double _lowerLoadFactor, _upperLoadFactor;
    int _capacity, _currSize;
public:
    //-------------------------------------- constructors --------------------------------------
    explicit HashMap(double lowerLoadFactor = 0.25, double upperLoadFactor = 0.75)
            : _lowerLoadFactor(lowerLoadFactor), _upperLoadFactor(upperLoadFactor),
              _capacity{16}, _currSize(0)
    {}

    HashMap(std::vector<KeyT> keysVec, std::vector<ValueT> valuesVec)
    {}

    //-------------------------------------- methods --------------------------------------

    int size() { return this->_currSize; }

    int capacity() { return this->_capacity; }

    double getLoadFactor() { return (double) _currSize / _capacity; }

    bool empty() { return !_currSize; }


};


#endif //EX3_HASHMAP_HPP
