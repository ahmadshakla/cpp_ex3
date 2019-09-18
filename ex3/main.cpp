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

    HashMap<int , int > hashMap;

    HashMap<int , int > hashMap2 = std::move(hashMap);
        std::cout<<hashMap2.capacity()<<std::endl;




//    std::cout<<hashMap.empty()<<std::endl;
//    for (int i = 0; i <14 ; ++i)
//    {
//        hashMap.insert(i,i*i);
//        hashMap2.insert(i,i*i);
//    }
//    hashMap.insert(17,17);

    std::cout<<"1 size " << (hashMap==hashMap2) << std::endl;
//
//    hashMap[86] = 19;

//    HashMap<int,int>::iterator it = hashMap.begin();
//    it++;
//    it++;

//    std::cout << hashMap[86]<< "lol\n";

//    for (auto &it : hashMap)
//        std::cout << it.first << " => " << it.second << '\n';


//    for (int i = 0; i <15 ; ++i)
//    {
//        hashMap.erase(i);
//    }
//    std::cout<<hashMap.capacity()<<std::endl;


std::map<int,int > myMap;
myMap[0] = 1;
std::map<int ,int> myMap2(myMap);
myMap[23] = 2343;
//    std::cout<<myMap.size()<<std::endl;
    myMap.erase(23);
//    std::cout<<(myMap.at(234234) == 234)<<std::endl;


//myMap2["hi"] = "bye";
//myMap2 = myMap;







}
