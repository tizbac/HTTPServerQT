cmake_minimum_required(VERSION 2.6)
project(httpserverqt)
find_package(Qt4 REQUIRED)

enable_testing()

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(HTTPServerQT_SRCS HTTPServerQT.cpp main.cpp)

qt4_automoc(${HTTPServerQT_SRCS})
add_executable(httpserverqt ${HTTPServerQT_SRCS})
target_link_libraries(httpserverqt ${QT_QTCORE_LIBRARY})

add_subdirectory(tests)

install(TARGETS httpserverqt RUNTIME DESTINATION bin)
