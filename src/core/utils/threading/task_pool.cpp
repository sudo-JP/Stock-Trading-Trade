#include "task_pool.h"
#include <mutex>

void TaskPool::add_work(std::vector<std::function<void()>> funcs) {

    std::unique_lock<std::mutex> lock(mtx); 
    for (size_t i = 0; i < funcs.size(); i++) {
        works.push_back(funcs[i]);
    }

    cv.notify_all();
}


std::vector<std::function<void()>> TaskPool::get_work() {
    std::vector<std::function<void()>> jobs; 

    std::unique_lock<std::mutex> lock(mtx); 
    cv.wait(lock, [this] { return !works.empty(); }); 
    size_t len = works.size() > CHUNK ? CHUNK : works.size(); 
    for (size_t i = 0; i < len; i++) {
        auto func = works.front();

        works.pop_front();
        jobs.push_back(func);
    }
    return jobs; 
}
