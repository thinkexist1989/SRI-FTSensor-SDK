cmake_minimum_required(VERSION 3.10)

project(SRI-FTSensor-SDK)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system thread)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test test.cpp)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test Boost::system Boost::thread Threads::Threads)
