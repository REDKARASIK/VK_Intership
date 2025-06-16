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
            datetime_ = parse_time_with_miliseconds(datetime);
        } else {
            datetime_ = boost::posix_time::microsec_clock::local_time();
        }
        std::cout << datetime_ << std::endl;
    }
    Metric(const Metric& other) = default;
    Metric(Metric&& other) = default;
    ~Metric() = default;

    static boost::posix_time::ptime parse_time_with_miliseconds(const std::string& time) {
        static const boost::regex re(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}$)", boost::regex::perl | boost::regex::no_except);
        if (!boost::regex_match(time, re)) {
            throw std::runtime_error("timestamp must be 'YYYY-MM-DD HH:MM:SS.mmm'");
        }
        std::istringstream iss(time);
        iss.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%Y-%m-%d %H:%M:%S%F")));
        boost::posix_time::ptime pt;
        iss >> pt;
        if (pt.is_not_a_date_time()) {
            throw std::runtime_error("failed to parse timestamp");
        }
        return pt;
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << metric_title_ << ' ' << value_;
        return oss.str();
    }

private:
    T value_;
    std::string metric_title_;
    boost::posix_time::ptime datetime_;
};