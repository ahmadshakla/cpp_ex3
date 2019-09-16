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
//    std::cout<<hashMap.empty()<<std::endl;
    hashMap.insert(98,4);
////    std::cout<<hashMap.containsKey(98)<<std::endl;
//    int i = 98;
    hashMap.at(98) = 12;
    std::cout<<hashMap.at(98)<<std::endl;

//    std::cout<<hashMap.at(9546);
    std::vector<int> myVec;
    myVec.push_back(1);
    myVec.push_back(2);
    myVec.push_back(3);
    myVec.erase(myVec.begin()+2);
//    for (const int &i:myVec)
//    {
//        std::cout<<myVec[i]<<std::endl;
//
//    }
//    myVec.at(1) =4;
//    std::cout<<myVec[1]<<std::endl;
    std::map<int,bool > myMap;

        std::cout<<myMap[4]<<std::endl;






}
