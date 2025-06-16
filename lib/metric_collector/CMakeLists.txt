add_library(MetricsCollector metric_collector.cpp metric_collector.h)
target_link_libraries(MetricsCollector PRIVATE Metric Boost::date_time Boost::regex)
target_include_directories(MetricsCollector PUBLIC ${PROJECT_SOURCE_DIR})