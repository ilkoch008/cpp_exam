#ifndef CPP_EXAM_MY_UNORDERED_MAP_ATOMIC_FLAG_H
#define CPP_EXAM_MY_UNORDERED_MAP_ATOMIC_FLAG_H

#include <unordered_map>
#include <atomic>

using namespace std;

template<typename Key, typename T>
class my_unordered_map_atomic_flag{
public:
    typedef typename unordered_map<Key, T>::const_iterator      iterator;
    typedef typename unordered_map<Key, T>::node_type           node_type;
    typedef typename unordered_map<Key, T>::insert_return_type  insert_return_type;
    typedef typename unordered_map<Key, T>::key_type            key_type;
    typedef typename unordered_map<Key, T>::value_type          value_type;

    my_unordered_map_atomic_flag() {
        inner_map = unordered_map<Key, T>();
    }

    my_unordered_map_atomic_flag(const my_unordered_map_atomic_flag&) = default;

    my_unordered_map_atomic_flag(my_unordered_map_atomic_flag&&) = default;

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
        while (lock.test_and_set()){
            this_thread::yield();
        }
        auto res = inner_map.find(x);
        lock.clear();
        return res;
    }

    template<typename Pair>
    __enable_if_t<is_constructible<value_type, Pair&&>::value,
    pair<iterator, bool>>
    insert(Pair&& p)
    {
        while (lock.test_and_set()){
            this_thread::yield();
        }
        auto res = inner_map.insert(p);
        lock.clear();
        return res;
    }

    size_t
    erase(const key_type& x)
    {
        while (lock.test_and_set()){
            this_thread::yield();
        }
        auto res = inner_map.erase(x);
        lock.clear();
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
    atomic_flag lock = ATOMIC_FLAG_INIT;
};

#endif //CPP_EXAM_MY_UNORDERED_MAP_ATOMIC_FLAG_H
