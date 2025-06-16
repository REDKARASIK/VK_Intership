add_library(MetricsCollector metrics_collector.cpp metrics_collector.h)
target_link_libraries(MetricsCollector PRIVATE Metric Boost::date_time Boost::regex)
target_include_directories(MetricsCollector PUBLIC ${PROJECT_SOURCE_DIR})