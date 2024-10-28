cmake_minimum_required(VERSION 3.10)
project(MyServerApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyServerApp main.cpp server.cpp)