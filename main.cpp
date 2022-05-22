#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include "my_unordered_map_mutex.h"
#include "my_unordered_map_atomic_flag.h"

#define N_OPS 100000
#define RANGE 1000

//typedef my_unordered_map_mutex<int, int> my_map;
typedef my_unordered_map_atomic_flag<int, int> my_map;


int rand_in_range(int min, int max){
    return (rand()%(max-min)) + min;
}

template<typename M>
void print_all(M& dict){
    for_each(dict.begin(), dict.end(), [](auto iter){cout<<iter.first<<" "<<iter.second<<endl;});
}

template<typename M>
void write_flooder(M& dict){
    for(int i = 0; i < N_OPS; i++){
        dict.insert(pair(rand_in_range(0, RANGE), rand_in_range(0, RANGE)));
        dict.erase( rand_in_range(0, RANGE));
    }
}

template<typename M>
void read_flooder(M& dict, int n_threads){
    for(int i = 0; i < N_OPS * n_threads * 2; i++){
        dict.find( rand_in_range(0, RANGE));
    }
}

template<typename M>
void bench(M& dict, int n_threads){
    std::vector<thread> threads;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i < n_threads; i++) {
        threads.emplace_back(write_flooder<my_map>, ref(dict));
    }
    read_flooder(dict, n_threads);
    for (int i = 0; i < n_threads; i++) {
        threads[i].join();
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << n_threads << ", "
    << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << endl;
}

int main()
{
    my_map dict;

    for (int i = 0; i < 11; ++i) {
        bench(dict, i);
    }

    return 0;
}