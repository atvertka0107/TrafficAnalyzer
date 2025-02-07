cmake_minimum_required(VERSION 3.10)

project(packet_classifier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

link_directories(${CMAKE_SOURCE_DIR}/libpcap)

include_directories(include)

file(GLOB SOURCES "source/*.cpp" "main.cpp")

add_executable(application_1 ${SOURCES})

target_link_libraries(application_1 pcap)