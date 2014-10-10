include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(HTTPServerQTTest_SRCS HTTPServerQTTest.cpp)

qt4_automoc(${HTTPServerQTTest_SRCS})
add_executable(HTTPServerQTTest ${HTTPServerQTTest_SRCS})
add_test(HTTPServerQTTest HTTPServerQTTest)
target_link_libraries(HTTPServerQTTest ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY})
