#include <iostream>
#include <vector>
#include <map>

#include "HashMap.hpp"

class Dog
{
public:
    int age;
    Dog(){
        age = 0;
    };
};

int main()
{
    Dog dog;
    std::pair<int,int> myOau(1,2);
    std::pair<int,int> myOau2(1,3);

    HashMap<int, int > hashMap;
    std::cout<<hashMap.empty()<<std::endl;
    hashMap.insert(98,4);
    std::cout<<hashMap.containsKey(198)<<std::endl;
    std::cout<<hashMap.getLoadFactor()<<std::endl;




}
