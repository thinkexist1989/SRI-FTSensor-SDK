cmake_minimum_required(VERSION 3.10)

project(examples)

add_executable(test test.cpp)
target_link_libraries(test SRI::FTSensor)