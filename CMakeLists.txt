cmake_minimum_required(VERSION 3.31)

project(
    MetricsHandler
    LANGUAGES CXX
    VERSION 1.0
)
set(CMAKE_CXX_STANDARD 23)

include_directories(lib)

include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES date_time regex)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
    URL_MD5 893b5203b862eb9bbd08553e24ff146a
)
FetchContent_MakeAvailable(Boost)
add_subdirectory(bin)
add_subdirectory(lib)