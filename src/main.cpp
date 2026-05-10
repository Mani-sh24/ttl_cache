#include <iostream>
#include "Cache.h"
#include<string>
int main()
{
    Cache<int , int> mc;
    mc.put(1, 2 , 100); // key 1 value 2 expiry 100seconds auto = no exipiration
    mc.put(2, 4); // no expiration
    mc.get(1);
    mc.get(2);
    mc.cleanExpired(); // manually clean expired keys from heap
    Cache<std::string , int> mc1(true , 10); // auto cleaning expired keys every 10 seconds -> flag to turn on auto clean , interval

    return 0;
}