
project(httpserverqt)
cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0020 NEW)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Network )
add_library(httpserverqt STATIC HTTPServerQT.cpp HTTPServerQT.h httpserver.cpp httpserver.h httpclient.cpp httpclient.h)
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )


  

qt5_use_modules(httpserverqt Core Network )

#install(TARGETS httpserverqt RUNTIME DESTINATION lib)
