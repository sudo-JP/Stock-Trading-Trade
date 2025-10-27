#include "task_pool.h"
#include <mutex>
#include <utility>

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


std::vector<std::pair<std::function<void()>, std::string>> TaskPool::get_work() {
    std::vector<std::pair<std::function<void()>, std::string>> jobs; 

    std::unique_lock<std::mutex> lock(mtx); 
    cv.wait(lock, [this] { return !works.empty(); }); 
    size_t len = works.size() > CHUNK ? CHUNK : works.size(); 
    for (size_t i = 0; i < len; i++) {
        auto func = works.front();
        auto sym = symbols.front();

        works.pop_front();
        symbols.pop_front(); 
        jobs.emplace_back(func, sym);
    }
    return jobs; 
}
