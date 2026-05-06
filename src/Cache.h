#ifndef CACHE_HPP
#define CACHE_HPP

#include <unordered_map>
#include <chrono>

template <typename Value>
struct CacheItem
{
    Value value;
    std::chrono::steady_clock::time_point expiry;
};

template <typename KeyType, typename ValueType>
class Cache
{
private:
    std::unordered_map<KeyType, CacheItem<ValueType>> m_cache_storage;

public:
    void put(const KeyType &key, const ValueType &value, int expiry = -1)
    {
        CacheItem<ValueType> item;
        item.value = value;

        if (expiry == -1)
        {
            item.expiry = std::chrono::steady_clock::time_point::max();
        }
        else
        {
            item.expiry = std::chrono::steady_clock::now() + std::chrono::seconds(expiry);
        }

        m_cache_storage[key] = item;
    }

    ValueType get(const KeyType &key)
    {
        auto it = m_cache_storage.find(key);

        if (it == m_cache_storage.end())
        {
            return ValueType{};
        }

        if (std::chrono::steady_clock::now() >= it->second.expiry)
        {
            m_cache_storage.erase(it);
            return ValueType{};
        }

        return it->second.value;
    }

    bool exists(const KeyType &key)
    {
        auto it = m_cache_storage.find(key);

        if (it == m_cache_storage.end())
        {
            return false;
        }

        if (std::chrono::steady_clock::now() >= it->second.expiry)
        {
            m_cache_storage.erase(it);
            return false;
        }

        return true;
    }

    void remove(const KeyType &key)
    {
        m_cache_storage.erase(key);
    }
};

#endif