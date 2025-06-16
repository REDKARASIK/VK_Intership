#include "metric_collector.h"

MetricCollector::MetricCollector(size_t capacity) :
    sem_(0),
    capacity_(capacity)
    {}

MetricCollector::~MetricCollector() {
    stop();
}

void MetricCollector::start(const std::string& output_file) {
    file_.open(output_file, std::ios::out | std::ios::app);
    if (!file_.is_open()) {
        throw std::runtime_error(std::string("Cannot open current file for metrics: ") + output_file);
    }
    worker_ = std::thread([this]{saver();});
}

void MetricCollector::saver() {
    while (true) {
        sem_.acquire();
        if (done_.load(std::memory_order_relaxed)) {
            break;
        }
        std::unique_ptr<IMetric> item;
        {
            std::scoped_lock lk(mtx_);
            if (!queue_.empty()) {
                item = std::move(queue_.front());
                queue_.pop();
            }
        }
        if (item) {
            file_ << item->to_string() << '\n';
        }
    }
}

void MetricCollector::stop() {
    done_.store(true, std::memory_order_relaxed);
    sem_.release();
    if (worker_.joinable()) {
        worker_.join();
    }
    if (file_.is_open()) {
        file_.close();
    }
}
