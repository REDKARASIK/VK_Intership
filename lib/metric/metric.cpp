#include "metric.h"

boost::posix_time::ptime IMetric::parse_time_with_milliseconds(const std::string& time) {
    static const boost::regex re(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{6}$)", boost::regex::perl | boost::regex::no_except);
    if (!boost::regex_match(time, re)) {
        throw std::runtime_error("timestamp must be 'YYYY-MM-DD HH:MM:SS.mmmmmm'");
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