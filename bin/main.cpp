#include <iostream>
#include "lib/metric/metric.h"
#include "lib/metric_collector/metric_collector.h"

int main(int argc, char** argv) {
    Metric<float> cpu("CPU", 0.97, "234");
    std::cout << cpu.get_datetime();
    return 0;
}