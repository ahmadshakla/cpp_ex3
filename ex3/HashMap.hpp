//
// Created by ahmad.shakla on 9/15/19.
//
#include <iostream>
#include <bits/unique_ptr.h>

#ifndef CPP_EX3_HPP
#define CPP_EX3_HPP

template <typename KeyT,typename ValueT>
class HashMap
{
public:
    KeyT key;
    ValueT value;
    


};

int main()
{
    HashMap<int,double> hashMap(3,2);
    hashMap.value1 = 2.3;
    hashMap.key1 = 1;

}
#endif //EX3_HASHMAP_HPP
