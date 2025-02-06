cmake_minimum_required(VERSION 3.10)

project(packet_classifier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

include_directories(${PCAP_INCLUDE_DIRS})
link_directories(${PCAP_LIBRARY_DIRS})

include_directories(include)

file(GLOB SOURCES "source/*.cpp" "main.cpp")

add_executable(application_1 ${SOURCES})

target_link_libraries(application_1 PRIVATE ${PCAP_LIBRARIES})