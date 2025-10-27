#include <condition_variable>
#include <functional>
#include <string>
#include <mutex>
#include <vector> 
#ifndef _TASK_POOL_H_
#define _TASK_POOL_H_

// Using SoA for performance cache friendly 
// The vector of work and symbols are parallel
// They are circular work pool array

/*
    * We double the capacity by counting the free
    * space based on these conditions: 
    * If read_idx < write_idx, then 
    * we count free_space = read_idx + capacity - write_idx
    * because read_idx represents how many tasks already dealt with,
    * where write_idx represents the latest task behind the capacity 
    *
    * Otherwise, free_space = read_idx - write_idx - 1
    *
    * We double when free_space == 0
    * */
struct TaskPool {
    std::vector<std::function<void()>>work; 
    std::vector<std::string> symbols; 

    int read_idx = 0; // front idx
    int write_idx = 0; // last idx
    int capacity = 0; 

    std::mutex lock;
    std::condition_variable cv; 
};

#endif 
