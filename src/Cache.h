#ifndef CACHE_HPP
#define CACHE_HPP
#include <mutex>
#include <unordered_map>
#include <queue>
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
    std::mutex mtx;
    std::priority_queue<
        std::pair<std::chrono::steady_clock::time_point, KeyType>,
        std::vector<std::pair<std::chrono::steady_clock::time_point, KeyType>>,
        std::greater<std::pair<std::chrono::steady_clock::time_point, KeyType>>>
        pq;
    std::unordered_map<KeyType, CacheItem<ValueType>> m_cache_storage;

public:
    void put(const KeyType &key, const ValueType &value, int expiry = -1)
    {
        std::lock_guard<std::mutex> lock(mtx);
        CacheItem<ValueType> item;
        item.value = value;

        if (expiry == -1)
        {
            item.expiry = std::chrono::steady_clock::time_point::max();
        }
        else
        {
            item.expiry = std::chrono::steady_clock::now() + std::chrono::seconds(expiry);
            pq.push({item.expiry, key});
        }
        m_cache_storage[key] = item;
    }

    ValueType get(const KeyType &key)
    {
        std::lock_guard<std::mutex> lock(mtx);
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
        std::lock_guard<std::mutex> lock(mtx);
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
    void cleanExpired()
    {
        std::lock_guard<std::mutex> lock(mtx);
        while (!pq.empty())
        {
            std::pair<std::chrono::steady_clock::time_point, KeyType> minele = {pq.top().first, pq.top().second};
            if (minele.first >= std::chrono::steady_clock::now())
            {
                break;
            }
            std::cout << "cleaned key " << minele.second << std::endl;
            pq.pop();

            auto it = m_cache_storage.find(minele.second);

            // Lazy deletion check
            if (it != m_cache_storage.end() &&
                it->second.expiry == minele.first)
            {
                m_cache_storage.erase(it);
            }
        }
    }
    void remove(const KeyType &key)
    {
        std::lock_guard<std::mutex> lock(mtx);
        m_cache_storage.erase(key);
    }
};

#endif