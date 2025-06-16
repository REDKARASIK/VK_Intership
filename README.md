# Metric Collector / VK Internship
*A small C++23 homework-style project*

The library lets many threads **push metrics** into a queue while one background
thread writes them to a file.  
All metrics that share **exactly the same timestamp**
(`YYYY-MM-DD HH:MM:SS.ffffff`) are written on **one line**:
`2025-06-18 12:34:56.123456 "CPU" 0.81 "HTTP requests RPS" 49`


The queue size is limited (`capacity`).  
If it is full producers just **wait**—so no metric is lost.

---

## Features

* Template **`Metric<T>`** (name, typed value, timestamp).
* **`MetricCollector`**  
  * bounded queue (size = capacity)  
  * two C++20 semaphores (`std::counting_semaphore`) – classic producer/consumer  
  * background `std::thread` writes the file.
* No third-party deps except header-only **Boost.Date_Time**.

---

## Quick Start

```bash
git clone https://github.com/your-handle/metric-collector.git
cd metric-collector
mkdir build && cd build
cmake ..      # needs C++23 compiler + Boost
make          # builds library, demo
./demo        # creates metrics.log
cat metrics.log

