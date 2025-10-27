#include "task_pool.h"
#include <mutex>


/*
 * Assuming the works and symbols
 * vects are parallel and have equal length
 * */
void TaskPool::add_work(std::vector<std::function<void()>> funcs, std::vector<std::string> symbs) {

    std::unique_lock<std::mutex> lock(mtx); 
    for (size_t i = 0; i < funcs.size(); i++) {
        works.push_back(funcs[i]);
        symbols.push_back(symbs[i]); 
    }

    cv.notify_all();
}
