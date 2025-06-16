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
    std::string current_time;
    std::ostringstream line;
    auto flash = [&]{
        if (!current_time.empty() && line.tellp() > 0) {
            file_ << current_time << ' ' << line.str() << '\n';
            current_time.clear();
            line.str("");
            line.clear();
        }
    };
    while (true) {
        sem_.acquire();
        std::unique_ptr<IMetric> item;
        {
            std::scoped_lock lk(mtx_);
            if (!queue_.empty()) {
                item = std::move(queue_.front());
                queue_.pop();
            } else if (done_.load()) {
                break;
            }
        }
        if (item) {
            std::string time = boost::posix_time::to_iso_extended_string(item->get_datetime()).replace(10, 1, " ");
            if (current_time.empty()) {
                current_time = time;
            }
            if (current_time != time) {
                flash();
                current_time = time;
            }
            line << item->to_string() << " ";
        }
    }
    flash();
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
