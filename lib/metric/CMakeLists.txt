add_library(Metric metric.h metric.cpp)
target_link_libraries(Metric PRIVATE Boost::date_time Boost::regex)