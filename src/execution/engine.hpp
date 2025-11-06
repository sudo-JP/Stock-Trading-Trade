#include <atomic>

class Engine {
    public: 
        void start(); 
        void stop();
        bool connected();
    private: 
    std::atomic<bool> connection{true};
}; 
