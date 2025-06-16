#pragma once
#include "lib/metric/metric.h"
#include <semaphore>
#include <fstream>
#include <thread>
#include <atomic>
#include <mutex>
#include <memory>
#include <queue>

class MetricCollector final {
public:
    explicit MetricCollector(size_t capacity = 1024);
    ~MetricCollector();
    void start(const std::string& output_file = "metrics.log");
    void stop();
    template<typename M, typename... Args>
    void push(Args&&... args) {
        auto ptr = std::make_unique<M>(std::forward<Args>(args)...);
        {
            std::scoped_lock lk(mtx_);
            queue_.push(std::move(ptr));
        }
        sem_.release();
    }
    template<typename T>
    void push(const Metric<T>& metric) {
        auto ptr = std::make_unique<Metric<T>>(metric);
        {
            std::scoped_lock lk(mtx_);
            queue_.push(std::move(ptr));
        }
        sem_.release();
    }

    template<typename T>
    void push(Metric<T>&& metric) {
        auto ptr = std::make_unique<Metric<T>>(std::move(metric));
        {
            std::scoped_lock lk(mtx_);
            queue_.push(std::move(ptr));
        }
        sem_.release();
    }
private:
    void saver();

    std::counting_semaphore<> sem_;
    std::ofstream file_;
    std::thread worker_;
    std::mutex mtx_;
    std::atomic<bool> done_ = false;
    std::queue<std::unique_ptr<IMetric>> queue_;
    const size_t capacity_;
};