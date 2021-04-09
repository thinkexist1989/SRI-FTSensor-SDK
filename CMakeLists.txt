cmake_minimum_required(VERSION 3.10)

project(SRI-FTSensor-SDK)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add all source files in ./src/
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/sri/*)

add_library(SRIftsensor ${SRC} ${HEADER})
add_library(SRI::FTSensor ALIAS SRIftsensor)
target_include_directories(SRIftsensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(SRIftsensor Boost::boost Boost::system)




add_subdirectory(examples)