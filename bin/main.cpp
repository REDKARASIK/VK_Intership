#include <iostream>
#include "lib/metric_collector/metric_collector.h"
#include "lib/metric/metric.h"
#include <chrono>
#include <thread>

int main(int argc, char** argv) {
    MetricCollector collector{32};
    collector.start("metrics.log");
    collector.push<Metric<double>>("CPU", 0.72);
    collector.push<Metric<int>>("HTTP requests RPS", 55);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    collector.push<Metric<double>>("CPU", 0.81);
    collector.push<Metric<int>>("HTTP requests RPS", 49);
    collector.stop(); 
    return 0;
}
