#pragma once
#include <string>
#include <any>
#include <boost/date_time/posix_time/ptime.hpp>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdexcept>
#include <boost/regex.hpp>


class IMetric {
public:
    virtual ~IMetric() = default;
    virtual std::string to_string() const = 0;
    static boost::posix_time::ptime parse_time_with_milliseconds(const std::string& time);
    virtual boost::posix_time::ptime get_datetime() const = 0;
};

template<typename T>
class Metric final : public IMetric {
public:
    template<typename U = T>
    Metric(const std::string& name_metric,  U&& value, const std::string& datetime = "") :
    value_(std::forward<U>(value)),
    metric_title_(name_metric)
    {
        if (!datetime.empty()) {
            datetime_ = IMetric::parse_time_with_milliseconds(datetime);
        } else {
            datetime_ = boost::posix_time::microsec_clock::local_time();
        }
    }
    Metric(const Metric& other) = default;
    Metric(Metric&& other) = default;
    ~Metric() = default;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << '\"' << metric_title_ << '\"' << ' ' << value_;
        return oss.str();
    }

    boost::posix_time::ptime get_datetime() const override {return datetime_;}

private:
    T value_;
    std::string metric_title_;
    boost::posix_time::ptime datetime_;
};