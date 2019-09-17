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
//    std::cout<<hashMap.empty()<<std::endl;
    for (int i = 0; i <15 ; ++i)
    {
        hashMap.insert(i,i*i);
    }
//    HashMap<int,int>::iterator it = hashMap.begin();
    for (auto &it : hashMap)
        std::cout << it.first << " => " << it.second << '\n';


//    for (int i = 0; i <15 ; ++i)
//    {
//        hashMap.erase(i);
//    }
    std::cout<<hashMap.capacity()<<std::endl;


std::map<int,int > myMap;
myMap[0] = 1;
std::map<int ,int> myMap2(myMap);
//myMap2["hi"] = "bye";
//myMap2 = myMap;







}
