#ifndef CPP_EXAM_MY_UNORDERED_MAP_MUTEX_H
#define CPP_EXAM_MY_UNORDERED_MAP_MUTEX_H

#include <unordered_map>
#include <mutex>

using namespace std;

template<typename Key, typename T>
class my_unordered_map_mutex{
public:
    typedef typename unordered_map<Key, T>::const_iterator      iterator;
    typedef typename unordered_map<Key, T>::node_type           node_type;
    typedef typename unordered_map<Key, T>::insert_return_type  insert_return_type;
    typedef typename unordered_map<Key, T>::key_type            key_type;
    typedef typename unordered_map<Key, T>::value_type          value_type;

    my_unordered_map_mutex() {
        inner_map = unordered_map<Key, T>();
    }

    my_unordered_map_mutex(const my_unordered_map_mutex&) = default;

    my_unordered_map_mutex(my_unordered_map_mutex&&) = default;

    bool
    empty() const noexcept
    { return inner_map.empty(); }

    size_t
    size() const noexcept
    { return inner_map.size(); }

    size_t
    max_size() const noexcept
    { return inner_map.max_size(); }

    iterator
    find(const Key& x)
    {
        mutex.lock();
        auto res = inner_map.find(x);
        mutex.unlock();
        return res;
    }

    template<typename Pair>
    __enable_if_t<is_constructible<value_type, Pair&&>::value,
            pair<iterator, bool>>
    insert(Pair&& p)
    {
        mutex.lock();
        auto res = inner_map.insert(p);
        mutex.unlock();
        return res;
    }

    size_t
    erase(const key_type& x)
    {
        mutex.lock();
        auto res = inner_map.erase(x);
        mutex.unlock();
        return res;
    }

    iterator
    begin() noexcept
    { return inner_map.begin(); }

    iterator
    end() noexcept
    { return inner_map.end(); }

private:
    unordered_map<Key, T> inner_map;
    mutex mutex;
};

#endif //CPP_EXAM_MY_UNORDERED_MAP_MUTEX_H
