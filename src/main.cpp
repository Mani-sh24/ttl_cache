#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
template<typename KeyType , typename ValueType>
class Cache{
    public:
        unordered_map<KeyType , ValueType> cache_storage;
    public:
        void put(const KeyType &key , const ValueType value){
            cache_storage[key] = value;
        }
        ValueType get(const KeyType &key){
            return cache_storage.at(key);
        }
        bool exists(const KeyType &key){
            return cache_storage.find(key) != end();
        }
        void remove(const KeyType& key) {
            cache_storage.erase(key);
        }
};