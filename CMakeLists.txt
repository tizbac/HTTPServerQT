
project(httpserverqt)
cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0020 NEW)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Network )
add_library(httpserverqt STATIC HTTPServerQT.cpp HTTPServerQT.h httpserver.cpp httpserver.h httpclient.cpp httpclient.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR} )
target_link_libraries(httpserverqt Qt6::Core Qt6::Network)

  



#install(TARGETS httpserverqt RUNTIME DESTINATION lib)
