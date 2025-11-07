#include <condition_variable>
#include <functional>
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

        void addWork(std::vector<std::function<void()>>funcs);
        
        std::vector<std::function<void()>> getWork();
    private:
        std::deque<std::function<void()>>works; 

        std::mutex mtx;
        std::condition_variable cv; 
};


#endif 
