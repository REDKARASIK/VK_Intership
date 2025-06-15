#include "metric.h"

Metric::Metric(const std::string& metric_title, const std::any& value) :
    value_(value),
    metric_title_(metric_title)
    {}