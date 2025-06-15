#pragma once
#include <string>
#include <any>
#include <boost/date_time/posix_time/ptime.hpp>


class Metric final {
public:
    Metric(const std::string& name_metric,  const std::any& value);
    Metric(const Metric& other) = default;
    Metric(Metric&& other) = default;
    ~Metric() = default;

private:
    std::any value_;
    std::string metric_title_;
};