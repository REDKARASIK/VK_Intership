#include <iostream>
#include "lib/metric/metric.h"
#include "lib/metric_collector/metric_collector.h"

int main(int argc, char** argv) {
    Metric<float> cpu("CPU", 0.97);
    std::cout << cpu.to_string() << std::endl;
    return 0;
}