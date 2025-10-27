#include <condition_variable>
#include <functional>
#include <optional>
#include <string>
#include <mutex>
#include <deque>
#include <vector>
#define CHUNK 10 
#ifndef _TASK_POOL_H_
#define _TASK_POOL_H_

// Using SoA for performance cache friendly 
// The vector of work and symbols are parallel
// They are circular work pool array

class TaskPool {
    public: 
        TaskPool();

        void add_work(std::vector<std::function<void()>>funcs, std::vector<std::string> symbs);
        
        std::vector<std::pair<std::function<void()>, std::string>> get_work();
    private:
        std::deque<std::function<void()>>works; 
        std::deque<std::string> symbols; 

        std::mutex mtx;
        std::condition_variable cv; 
};


#endif 
